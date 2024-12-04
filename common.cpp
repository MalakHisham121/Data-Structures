#include <iostream>
#pragma once
using namespace std;
class Item {
public:
    string itemName;
    string category;
    int price;
    Item() {
        itemName = ' ';
        category = ' ';
        price = 0;
    }

    Item(string name, string cat, int pr) : itemName(name), category(cat), price(pr) {}

    string getItemName() const {
        return itemName;
    }
    int getItemprice(){
        return price;
    }

    string getItemcateg(){
        return category;
    }
    void print() const {
        cout << itemName << endl;
        cout << category << endl;
        cout << price << endl;
        cout<<endl;
    }

    string toLowerCase(const string& str) const {
        string result;
        for (char c : str) {
            result += tolower(c);
        }
        return result;
    }

    bool operator<(const Item& other) const {
        string name= toLowerCase(itemName);
        string otherName = toLowerCase(other.itemName);
        return name< otherName;
    }

    bool operator>(const Item& other) const {
        if (price == other.price) {
            return toLowerCase(itemName) > toLowerCase(other.toLowerCase(itemName));
        }
        return price > other.price;
    }
};

class Node {
public:
    Item item;
    Node* left;
    Node* right;
    Node* parent;

    Node(Item i) : item(i), left(nullptr), right(nullptr) {}
};
