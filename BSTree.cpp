#include <iostream>
#include <algorithm>

using namespace std;

class TreeNode {
public:
    Item x;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Item y) {
        x =y;
        left = nullptr;
        right = nullptr;
    }
};

class BST_price{
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node,Item item) {

        if (node == nullptr) {
            node = new TreeNode(item);
        }
        else if (item.price <node->x.price) {
            node->left = insert(node->left,item);
        }
        else {
            node->right = insert(node->right, item);
        }
        return node;
    }

    void ascending(TreeNode* node) {
        if (node != nullptr) {
            ascending(node->left);
            cout << "Name: " << node->x.getItemName() << ", Category: " << node->x.getItemName() << ", Price: " << node->x.getItemprice() << endl;
            ascending(node->right);
        }
    }
    void  descending(TreeNode* node) {
        if (node != nullptr) {
            descending(node->right);
            cout << "Name: " << node->x.getItemName()<< " Category: " << node->x.getItemcateg() << " Price: " << node->x.getItemprice() << endl;
            descending(node->left);
        }
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteNode(TreeNode* node,Item item) {
        if (node == nullptr) {
            return node;
        }

        if (item.price < node->x.price) {
            node->left = deleteNode(node->left,item);
        }
        else if (item.getItemName()> node->x.itemName) {
            node->right = deleteNode(node->right,item);
        }
        else if(item.itemName==node->x.itemName&& item.category==node->x.category && item.price==node->x.price) {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->right);
            node->x.itemName = temp->x.itemName;
            node->x.category = temp->x.category;
            node->x.price = temp->x.price;
            node->right = deleteNode(node->right,temp->x);
        }
        return node;
    }
public:
    BST_price() {
        root = nullptr;
    }
    void insert(Item x) {
        root = insert(root,x);
    }

    void sort_ascending() {
        if (root == nullptr) {
            cout << "BST is empty." << endl;
        }
        else {
            cout << "Items in BST:" << endl;
            ascending(root);
        }
    }
    void sort_descending() {
        if (root == nullptr) {
            cout << "BST is empty." << endl;
        }
        else {
            cout << "Items in BST:" << endl;
            descending(root);
        }
    }
    void deleteItem(Item x) {
        root = deleteNode(root,x);
    }
};
class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, Item item) {
if (node == nullptr) {
node = new TreeNode(item);
}
else if (item < node->x) {
node->left = insert(node->left, item);
}
else {
node->right = insert(node->right, item);
}
return node;
}

void ascending(TreeNode* node) {
    if (node != nullptr) {
        ascending(node->left);
        cout << "Name: " << node->x.itemName << ", Category: " << node->x.category << ", Price: " << node->x.price << endl;
        ascending(node->right);
    }
}
void  descending(TreeNode* node) {
    if (node != nullptr) {
        descending(node->right);
        cout << "Name: " << node->x.itemName << " Category: " << node->x.category << " Price: " << node->x.price << endl;
        descending(node->left);
    }
}

TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* deleteNode(TreeNode* node, Item item) {
    if (node == nullptr) {
        return node;
    }

    if (item.itemName < node->x.itemName) {
        node->left = deleteNode(node->left, item);
    }
    else if (item.itemName > node->x.itemName) {
        node->right = deleteNode(node->right, item);
    }
    else if (item.itemName == node->x.itemName && item.category == node->x.category && item.price == node->x.price) {
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        TreeNode* temp = minValueNode(node->right);
        node->x.itemName = temp->x.itemName;
        node->x.category = temp->x.category;
        node->x.price = temp->x.price;
        node->right = deleteNode(node->right, temp->x);
    }
    return node;
}
public:
BST() {
    root = nullptr;
}
void insert(Item x) {
    root = insert(root, x);
}

void sort_ascending() {
    if (root == nullptr) {
        cout << "BST is empty." << endl;
    }
    else {
        cout << "Items in BST:" << endl;
        ascending(root);
    }
}
void sort_descending() {
    if (root == nullptr) {
        cout << "BST is empty." << endl;
    }
    else {
        cout << "Items in BST:" << endl;
        descending(root);
    }
}
void deleteItem(Item x) {
    root = deleteNode(root, x);
}
};

BST bst;
BST_price bst1;

void insert(Item x) {
    bst.insert(x);
    bst1.insert(x);
}
void delete_item (Item x){
    bst.deleteItem(x);
    bst1.deleteItem(x);
}
void display_price_as() {
    bst1.sort_ascending();
}
void display_price_des() {
    bst1.sort_descending();
}
void display_name_as() {
    bst.sort_ascending();
}
void display_name_ds() {
    bst.sort_descending();
}
//int main() {
//
//
//
//    return 0;
//}
