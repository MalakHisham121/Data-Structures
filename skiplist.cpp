#include <iostream>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;
const int MAX_LEVEL = 16;
struct node {
    int value;
    node** forward;

    node(int level, int val) {
        this->value = val;
        this->forward = new node * [level + 1];
        for (int i = 0; i < level + 1; i++) {
            this->forward[i] = nullptr;
        }
    }
    ~node() {
        delete[] forward;
    }
};


class skip_list {
private:
    node* header;
    int max_level;

    int random_level() {
        int lev = 0;
        while (((float)rand() / RAND_MAX) < 0.5 && lev < MAX_LEVEL - 1) {
            lev++;
        }
        //cout<<"number of random levels: "<<lev<<endl;
        return lev;
    }

public:
    skip_list() {
        header = new node(MAX_LEVEL, -1);
        max_level = 0;
    }

    ~skip_list() {
        node* current = header;
        while (current) {
            node* next = current->forward[0];
            delete current;
            current = next;
        }
    }
    void insert(int val) {
        node* update[MAX_LEVEL + 1];
        node* current = header;
        for (int i = max_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < val) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        if (current == nullptr || current->value != val) {
            int new_level = random_level();
            if (new_level > max_level) {
                for (int i = max_level + 1; i <= new_level; i++) {
                    update[i] = header;
                }
                max_level = new_level;
            }
            node* new_node = new node(new_level, val);
            for (int i = 0; i <= new_level; i++) {
                new_node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = new_node;
            }
            cout << val << " is inserted in the skip list at level: ";
            for (int i = 0; i <= new_level; i++) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
    bool search(int val) {
        node* curr = header;

        for (int i = max_level; i >= 0; i--) {
            while (curr != nullptr && curr->forward[i]->value < val && curr->forward[i] != nullptr) {
                curr = curr->forward[i];
            }
        }

        curr = curr->forward[0];
        if (curr && curr->value == val) {
            cout << val << " is found in the skip list\n";
            return true;
        }
        else {
            cout << val << " isn't found in the skip list\n";
            return false;
        }

    }

    void delet(int val) {
        node* current = header;
        node* update[MAX_LEVEL + 1];

        for (int i = max_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < val) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->value == val) {
            for (int i = 0; i <= max_level; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (max_level > 0 && header->forward[max_level] == nullptr) {
                max_level--;
            }

            cout << val << " is removed from the skip list.\n";
        }
        else {
            cout << val << " isn't found in the skip list.\n";
        }
    }


    void print() {
        cout << "----------skip list----------" << endl;
        for (int i = max_level; i >= 0; i--) {
            node* curr_node = header->forward[i];
            cout << "level " << i << ": ";
            while (curr_node != nullptr) {
                cout << "|" << curr_node->value << "|" << " ";
                curr_node = curr_node->forward[i];
            }
            cout << endl;
        }
        cout << "-----------------------------" << endl;

    }






};
class player {
public:
    int Id;
    int Score;
    float Stamina;
    player** forward;
    player(int level, int Id, int Score) {
        this->Id = Id;
        this->Score = Score;
        Stamina = 100, 0;
        this->forward = new player * [level + 1];
        for (int i = 0; i < level + 1; i++) {
            this->forward[i] = nullptr;
        }
    }
    ~player() {
        delete[] forward;
    }

};
class skip_list_player {
private:
    priority_queue<int> heap;
    unordered_map<int, int> counter;
    player* header;
    int max_level;

    int random_level() {
        int lev = 0;
        while (((float)rand() / RAND_MAX) < 0.5 && lev < MAX_LEVEL - 1) {
            lev++;
        }
        //cout<<"number of random levels: "<<lev<<endl;
        return lev;
    }
    void UpdateStamina(player* current, float timeElapsed) {
        float staminaDecrease = timeElapsed * 0.5;
        current->Stamina = std::max(0.0f, current->Stamina - staminaDecrease);
    }
    void UpdateScores(float timeElapsed) {
        player* current = header->forward[0];
        while (current != nullptr) {

            UpdateStamina(current, timeElapsed);

            float staminaEffect = current->Stamina / 100.0;
            current->Score = static_cast<int>(current->Score * staminaEffect);
            current = current->forward[0];
        }
    }
    void RecoverStamina(player* current, float recoveryRate) {
        current->Stamina = std::min(100.0f, current->Stamina + recoveryRate); // Cap at 100
    }
public:
    skip_list_player() {
        header = new player(MAX_LEVEL,-1,-1);
        max_level = 0;
    }

    ~skip_list_player() {
        player* current = header;
        while (current) {
            player* next = current->forward[0];
            delete current;
            current = next;
        }
    }
    void AddPlayer(int Id,int Score) {
        player* update[MAX_LEVEL + 1];
        player* current = header;
        for (int i = max_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->Id < Id) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (current != nullptr && current->Id == Id) {
            cout << "Player with ID " << Id << " already exists." << endl;
            return;
        }
        else if(current == nullptr || current->Id != Id) {
            heap.push(Score);
            counter[Score]++;
            int new_level = random_level();
            if (new_level > max_level) {
                for (int i = max_level + 1; i <= new_level; i++) {
                    update[i] = header;
                }
                max_level = new_level;
            }
            player* new_node = new player(new_level, Id,Score);
            for (int i = 0; i <= new_level; i++) {
                new_node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = new_node;
            }
            cout << "Player " << Id << " added with score " << Score << ' ';
            for (int i = 0; i <= new_level; i++) {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    /*  void Updateplayer(int Id,int newScore) {
           player* curr = header;

           for (int i = max_level; i >= 0; i--) {
               while (curr !=nullptr  && curr->forward[i] != nullptr && curr->forward[i]->Id < Id) {
                   curr = curr->forward[i];
               }
           }
           curr = curr->forward[0];
           if (curr!=nullptr && curr->Id == Id) {
               curr->Score = newScore;

           }
           else {
               cout << Id << " isn't found in the  list\n";

           }

       }*/

    void RemovePlayer(int Id) {
        player* current = header;
        player* update[MAX_LEVEL + 1];

        for (int i = max_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->Id < Id) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->Id == Id) {
            for (int i = 0; i <= max_level; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (max_level > 0 && header->forward[max_level] == nullptr) {
                max_level--;
            }

            cout <<"Player" << Id << " is removed .\n";
        }
        else {
            cout <<"Player"<<Id << " isn't found .\n";
        }
    }


    void GetTopNPlayers(int N) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;


        player* current = header->forward[0];
        while (current != nullptr) {
            if (minHeap.size() < N) {
                minHeap.push({ current->Score, current->Id });
            }
            else if (current->Score > minHeap.top().first) {
                minHeap.pop();
                minHeap.push({ current->Score, current->Id });
            }
            current = current->forward[0];
        }


        vector<pair<int, int>> topPlayers;
        while (!minHeap.empty()) {
            topPlayers.push_back({ minHeap.top().second, minHeap.top().first });
            minHeap.pop();
        }


        sort(topPlayers.begin(), topPlayers.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });
        for (int i = 0; i < topPlayers.size(); i++)
        {
            cout <<"ID: " << topPlayers[i].first << " Score: " << topPlayers[i].second << endl;
        }

    }
    void print() {
        cout << "----------current player----------" << endl;
        for (int i = max_level; i >= 0; i--) {
            player* curr_player = header->forward[i];
            cout << "level " << i << ": ";
            while (curr_player != nullptr) {
                cout << "| ID: " << curr_player->Id << " Score: " << curr_player->Score << " Stamina: " << curr_player->Stamina << " | ";
                curr_player = curr_player->forward[i];
            }
            cout << endl;
        }
        cout << "-----------------------------" << endl;
    }

    void SimulateGame(float totalDuration, float updateInterval) {
        float elapsedTime = 0.0f;
        while (elapsedTime < totalDuration) {
            cout << "\nTime: " << elapsedTime << " units" << endl;
            UpdateScores(updateInterval);
            print();

            // Allow dynamic actions during simulation
            cout << "Enter command (add, remove, topn): ";
            string command;
            cin >> command;

            if (command == "add") {
                cout << "Enter the number of player you want to add: ";
                int t;
                cin >> t;
                while (t-- ) {
                    int id, score;
                    cout << "Enter player ID and score: ";
                    cin >> id >> score;
                    AddPlayer(id, score);
                }
            }
            else if (command == "remove") {
                cout << "Enter the number of player you want to remove: ";
                int t;
                cin >> t;
                while (t--) {
                    int id;
                    cout << "Enter player ID to remove: ";
                    cin >> id;
                    RemovePlayer(id);
                }
            }
            else if (command == "topn") {
                cout << "Enter number to Get the first n: ";
                int num;
                cin >> num;
                GetTopNPlayers(num);
            }
            else {
                cout << "Invalid command. Try again." << endl;
                break;
            }

            elapsedTime += updateInterval;
        }
    }


};


int main() {
    skip_list s;
    s.insert(52);
    s.insert(7);
    s.insert(0);
    s.insert(43);
    s.insert(87);


    s.print();
    s.search(0);
    s.search(33);
    s.delet(5);
    s.delet(0);
    s.print();
    cout << "/////////////////////////////////////////\n";

    skip_list_player players;

    players.SimulateGame(150,5);







    return 0;

}