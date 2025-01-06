#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <functional>
using namespace std;

const double A= 0.6180339887;
int div_method(int k, int t_size) {
    int pos=  k % t_size;
    return pos;
}

int multip_method(int k, int t_size) {
    double frac = k * A - floor(k * A);
    int pos = floor(frac * t_size);
    return pos;
}

int midsquare_method(int k, int n) {
    int k_square = k * k;
    string kk = to_string(k_square);
    int len = kk.length();
    int mid = len / 2;
    string mid_digit = kk.substr(max(0, mid - 1), 2);
    int mid_dig = stoi(mid_digit);
    int pos = mid_dig % n;
    return pos;
}

template<typename T>
vector<list<T>> ChainingMethod(vector<list<T>>& Hashtable, int value, int size) {
    int hashedKey = value % size;
    Hashtable[hashedKey].push_back(value);
    return Hashtable;
}

template<typename T>
bool SearchChaining(vector<list<T>>& Hashtable, int key, T value) {
    if (!Hashtable[key % Hashtable.size()].empty()) {
        for (auto v : Hashtable[key % Hashtable.size()]) {
            if (v == value) return true;
        }
    }
    return false;
}

template<typename T>
vector<T> OpenAddressingMethod(vector<T>& Hashtable, int key, int size, int type) {
    int hashedKey = key % size;
    int NewhashedKey = hashedKey;
    int itertor = 1;
    if (Hashtable[NewhashedKey]) {
        do {
            if (type == 1)
                NewhashedKey = NewhashedKey + itertor;
            else {
                NewhashedKey = NewhashedKey + (itertor * itertor);
            }
            NewhashedKey %= size;
            itertor++;
        } while (Hashtable[NewhashedKey] && NewhashedKey != hashedKey);
    }
    Hashtable[NewhashedKey] = key;
    return Hashtable;
}

template<typename T>
bool SearchOpenAddressing(vector<T>& Hashtable, int key, T value, int type) {
    int tempKey = key % Hashtable.size();
    int it = 1;
    if (type == 1) {
        do {
            if (Hashtable[tempKey] == value) return true;
            if (Hashtable[tempKey] == 0) break;
            tempKey++;
            tempKey %= Hashtable.size();
        } while (tempKey != key);
        return false;
    } else {
        vector<bool> vis(Hashtable.size());
        do {
            if (Hashtable[tempKey] == value) return true;
            if (Hashtable[tempKey] == 0) break;
            tempKey += (it * it);
            it++;
            tempKey %= Hashtable.size();
        } while (!vis[tempKey % Hashtable.size()]);
        return false;
    }
}

template<typename T>
vector<T> DoubleHashingMethod(vector<T>& Hashtable, int value, int& actualelements) {
    int prime;
    function<void(vector<T>&)> rehash = [&](vector<T> HashTable) -> void {
        Hashtable.resize(2 * Hashtable.size());
    };
    actualelements++;
    if ((actualelements) / Hashtable.size() > 0.7) rehash(Hashtable);
    function<bool(int)> isPrime = [&](int lessValue) -> bool {
        for (int i = 2; i * i <= lessValue; i++) {
            if (lessValue % i == 0) return false;
        }
        return true;
    };
    function<int(int)> getPrime = [&](int lessValue) -> int {
        while (!isPrime(lessValue))
            lessValue++;
        return lessValue;
    };
    prime = getPrime(Hashtable.size());
    int hash1 = value % Hashtable.size();
    int hash2 = hash1 % prime;
    while (Hashtable[hash2]) {
        rehash(Hashtable);
        hash1 = value % Hashtable.size();
        prime = getPrime(Hashtable.size());
        hash2 = hash1 % prime;
    }
    Hashtable[hash2] = value;
    return Hashtable;
}

vector<int> partition_key(const string& key, int part_size) {
    vector<int> parts;
    for (size_t i = 0; i < key.size(); i += part_size) {
        string part = key.substr(i, part_size);
        parts.push_back(stoi(part));
    }
    return parts;
}

int fold_shifting(const string& key, int addressSpace) {
    int part_size = (key.size() - (key.size() % addressSpace)) / (key.size() / addressSpace);
    vector<int> parts = partition_key(key, part_size);
    int sum = 0;
    for (int i : parts) {
        sum += i;
    }
    return sum % static_cast<int>(pow(10, addressSpace));
}

int fold_boundary(const string& key, int addressSpace) {
    int part_size = (key.size() - (key.size() % addressSpace)) / (key.size() / addressSpace);
    vector<int> parts = partition_key(key, part_size);
    if (!parts.empty()) {
        string first_part = to_string(parts.front());
        string last_part = to_string(parts.back());
        reverse(first_part.begin(), first_part.end());
        reverse(last_part.begin(), last_part.end());
        parts.front() = stoi(first_part);
        parts.back() = stoi(last_part);
    }
    int sum = 0;
    for (int i : parts) {
        sum += i;
    }
    return sum % static_cast<int>(pow(10, addressSpace));
}

int main() {

    cout<<fold_shifting("56789",2);


    cout << "\nTesting Chaining Method and Search: \n";
    vector<list<int>> chainTable(10);
    ChainingMethod(chainTable, 15, 10);
    ChainingMethod(chainTable, 25, 10);
    ChainingMethod(chainTable, 35, 10);
    for (int i = 0; i < 10; i++) {
        cout << "Bucket " << i << ": ";
        for (int val : chainTable[i]) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "\nSearching for 15 in Chaining: ";
    cout << (SearchChaining(chainTable, 15, 15) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100 in Chaining: ";
    cout << (SearchChaining(chainTable, 15, 100) ? "Found" : "Not Found") << endl;

    cout << "\nTesting Open Addressing (Linear Probing) and Search: \n";
    vector<int> openAddressingTable(10);
    OpenAddressingMethod(openAddressingTable, 15, 10, 1);
    OpenAddressingMethod(openAddressingTable, 25, 10, 1);
    OpenAddressingMethod(openAddressingTable, 35, 10, 1);
    for (int i = 0; i < openAddressingTable.size(); i++) {
        cout << "Index " << i << ": " << openAddressingTable[i] << endl;
    }

    cout << "\nSearching for 15 in Open Addressing (Linear Probing): ";
    cout << (SearchOpenAddressing(openAddressingTable, 15, 15, 1) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100 in Open Addressing (Linear Probing): ";
    cout << (SearchOpenAddressing(openAddressingTable, 15, 100, 1) ? "Found" : "Not Found") << endl;

    cout << "\nTesting Open Addressing (Quadratic Probing) and Search: \n";
    vector<int> openAddressingTableQuad(10);
    OpenAddressingMethod(openAddressingTableQuad, 15, 10, 2);
    OpenAddressingMethod(openAddressingTableQuad, 25, 10, 2);
    OpenAddressingMethod(openAddressingTableQuad, 35, 10, 2);
    for (int i = 0; i < openAddressingTableQuad.size(); i++) {
        cout << "Index " << i << ": " << openAddressingTableQuad[i] << endl;
    }

    cout << "\nSearching for 15 in Open Addressing (Quadratic Probing): ";
    cout << (SearchOpenAddressing(openAddressingTableQuad, 15, 15, 2) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100 in Open Addressing (Quadratic Probing): ";
    cout << (SearchOpenAddressing(openAddressingTableQuad, 15, 100, 2) ? "Found" : "Not Found") << endl;

    return 0;
}
