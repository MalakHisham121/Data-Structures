#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#ifndef ADVANCED_DATA_STRUCTURES_BTREE_H
#define ADVANCED_DATA_STRUCTURES_BTREE_H

using namespace std;

// Author Malak Hisham
// Date 9/12/2024

template<class T, int order>
struct BTreeNode {
    BTreeNode* parent;
    vector<T> keys;
    vector<BTreeNode<T, order>*> children;
    bool leaf;

    BTreeNode() : parent(nullptr), leaf(false) {}

    ~BTreeNode() {
        for (auto* child : children) {
            delete child;
        }
        children.clear();
    }
};

template<class T, int order>
class BTree {
    BTreeNode<T, order>* root;

public:
    BTree() : root(nullptr) {}

    ~BTree() {
        delete root;
    }

    void Insert(T value) {
        if (!root) {
            root = new BTreeNode<T, order>();
            root->leaf = true;
            root->keys.push_back(value);
            return;
        }

        BTreeNode<T, order>* current = root;
        while (!current->leaf) {
            size_t i = 0;
            while (i < current->keys.size() && value > current->keys[i]) i++;
            current = current->children[i];
        }

        // Insert into the leaf node
        current->keys.insert(upper_bound(current->keys.begin(), current->keys.end(), value), value);

        // Handle overflow
        while (current->keys.size() == order) {
            if (!current->parent) {
                // Create a new root if splitting the original root
                BTreeNode<T, order>* newRoot = new BTreeNode<T, order>();
                newRoot->leaf = false;
                newRoot->children.push_back(current);
                current->parent = newRoot;
                root = newRoot;
            }

            split(current);
            current = current->parent;
        }
    }

    void split(BTreeNode<T, order>* node) {
        size_t midIndex = order / 2;
        T median = node->keys[midIndex];

        // Create new right node
        BTreeNode<T, order>* rightNode = new BTreeNode<T, order>();
        rightNode->leaf = node->leaf;
        rightNode->keys.assign(node->keys.begin() + midIndex + 1, node->keys.end());
        node->keys.resize(midIndex);

        if (!node->leaf) {
            rightNode->children.assign(node->children.begin() + midIndex + 1, node->children.end());
            for (auto* child : rightNode->children) {
                child->parent = rightNode;
            }
            node->children.resize(midIndex + 1);
        }

        // Insert median into parent
        BTreeNode<T, order>* parent = node->parent;
        size_t insertPos = upper_bound(parent->keys.begin(), parent->keys.end(), median) - parent->keys.begin();
        parent->keys.insert(parent->keys.begin() + insertPos, median);
        parent->children.insert(parent->children.begin() + insertPos + 1, rightNode);
        rightNode->parent = parent;
    }

    void Print()  {
        string output = "";
        function<string(BTreeNode<T, order> *)> dfs = [&](BTreeNode<T, order> *current) -> string {
            if (current == nullptr)return "";
            int u = current->keys.size() - 1;
            for (int i = 0; i < current->keys.size(); i++) {
                cout << current->keys[i];
                if (u)u--, cout << '.';

            }
            output += "  ";


            if (!current->leaf) {
                //  cout<<"\n";
                for (int i = 0; i < current->children.size(); i++) {

                    //cout<<i<<' ';
                    if (i < current->children.size() && current->children[i] != nullptr) {
                        cout << '\n' << output;
                        dfs(current->children[i]);
                        output.pop_back();
                        output.pop_back();
                    }
                }
            }
            return output;
        };

        cout << dfs(root) << '\n';
    }
    };

#endif // ADVANCED_DATA_STRUCTURES_BTREE_H
