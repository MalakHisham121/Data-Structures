#include <iostream>
#include <functional>
using namespace std;

template<typename T>
class RBNode {
public:
    bool color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    T value;
    RBNode() {
        color = true;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class RBTree {
    RBNode<T>* root;

    void deleteSubtree(RBNode<T>* node) {
        if (!node) return;
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }

public:
    RBTree() {
        root = nullptr;
    }

    ~RBTree() {
        deleteSubtree(root);
    }

    void Insert(T val) {
        if (!root) {
            RBNode<T>* node = new RBNode<T>();
            node->value = val;
            root = node;
            node->color = 0;
        } else {
            RBNode<T>* node = search(root, val);
            RBNode<T>* Newnode = new RBNode<T>();
            Newnode->value = val;
            Newnode->parent = node;
            if (val < node->value) {
                node->left = Newnode;
            } else {
                node->right = Newnode;
            }
            fix(Newnode);
        }
    }

    void fix(RBNode<T>* &node) {
        while (node->parent && node->parent->color && node->color) {
            RBNode<T>* grandparent = node->parent->parent;

            if (grandparent) {
                if (node->parent == grandparent->left) {
                    RBNode<T>* uncle = grandparent->right;

                    if (uncle && uncle->color) {
                        grandparent->left->color = 0;
                        grandparent->right->color = 0;
                        grandparent->color = 1;
                        node = grandparent;
                    }
                    else { // uncle is black
                        if (node == node->parent->right) { // I am right of parent and uncle is black
                           node = node->parent;
                            LeftRotate(node, node->parent);
                        }
                        node->parent->color = 0;
                        grandparent->color = 1;
                        RightRotate(grandparent, node->parent);
                    }
                }
                else {
                    RBNode<T>* uncle = grandparent->left;

                    if (uncle && uncle->color) {
                        grandparent->left->color = 0;
                        grandparent->right->color = 0;
                        grandparent->color = 1;
                        node = grandparent;
                    } else {
                        if (node == node->parent->left) {
                            node = node->parent;
                            RightRotate(node, node->parent);
                        }
                        node->parent->color = 0;
                        grandparent->color = 1;
                        LeftRotate(grandparent, node->parent);
                    }
                }
            }
            else {
                break;
            }
        }
        root->color = 0;
    }

    RBNode<T>* search(RBNode<T>* current, T val) {
        if (!current || val == current->value) return current;
        if (val < current->value) {
            if (!current->left) return current;
            return search(current->left, val);
        } else {
            if (!current->right) return current;
            return search(current->right, val);
        }
    }

    void RightRotate(RBNode<T>*  & a, RBNode<T>* & b) {
        if (root == a) {
            root = b;
        }

        if (a->parent) {
            if (a->parent->left == a) {
                a->parent->left = b;
            } else {
                a->parent->right = b;
            }
        }

        b->parent = a->parent;

        a->left = b->right;
        if (b->right) {
            b->right->parent = a;
        }

        b->right = a;
        a->parent = b;

    }

    void LeftRotate(RBNode<T>* & a, RBNode<T>*  & b) {
        if (a->parent) {
            if (a == a->parent->left) {
                a->parent->left = b;
            } else {
                a->parent->right = b;
            }
        }
        if(a->parent)
            b->parent = a->parent;
        a->parent = b;
        a->left = b->left;
        a->right = nullptr;
        if (b->left) b->left->parent = a;
        if(root==a)root =b;
        b->left = a;
    }

    void Delete(T val) {
        RBNode<T>* node = search(root, val);
        if (!node || node->value != val) {
            cout << "The value not found";
            return;
        }

        RBNode<T>* replacement = nullptr;
        RBNode<T>* toDelete = node;
        bool originalColor = toDelete->color;

        if (!node->left) {
            replacement = node->right;
            transplant(node, node->right);
        } else if (!node->right) {
            replacement = node->left;
            transplant(node, node->left);
        } else {
            toDelete = getMinimum(node->right);
            originalColor = toDelete->color;
            replacement = toDelete->right;
            if (toDelete->parent == node) {
                if (replacement) replacement->parent = toDelete;
            }
            else {
                transplant(toDelete, toDelete->right);
                toDelete->right = node->right;
                toDelete->right->parent = toDelete;
            }
            transplant(node, toDelete); // replace node with the sus
            toDelete->left = node->left;
            toDelete->left->parent = toDelete;
            toDelete->color = node->color;
        }

        if (originalColor == 0) {
            fixDoubleBlack(replacement, toDelete->parent);
        }
    }

    void fixDoubleBlack(RBNode<T>* node, RBNode<T>* parent) {
        while (node != root && (!node || node->color == 0)) {
            if (node == parent->left) {
                RBNode<T>* sibling = parent->right;

                if (sibling&&sibling->color == 1) {
                    sibling->color = 0;
                    parent->color = 1;
                    LeftRotate(parent, sibling);
                    sibling = parent->right;
                }

                bool leftBlack = (!sibling||!sibling->left || sibling->left->color == 0);
                bool rightBlack = (!sibling||!sibling->right || sibling->right->color == 0);

                if (leftBlack && rightBlack) {
                    if(sibling)
                    sibling->color = 1;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (rightBlack) {
                        sibling->left->color = 0;
                        sibling->color = 1;
                        RightRotate(sibling, sibling->left);
                        sibling = parent->right;
                    }

                    sibling->color = parent->color;
                    parent->color = 0;
                    sibling->right->color = 0;
                    LeftRotate(parent, sibling);
                    node = root;
                }
            }
            else {
                RBNode<T>* sibling = parent->left;
                if (sibling&&sibling->color == 1) {
                    sibling->color = 0;
                    parent->color = 1;
                    RightRotate(parent, sibling);
                    sibling = parent->left;
                }

                bool leftBlack = (!sibling&&!sibling->left || sibling->left->color == 0);
                bool rightBlack = (!sibling&&!sibling->right || sibling->right->color == 0);

                if (leftBlack && rightBlack) {
                    if(sibling)
                    sibling->color = 1;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (leftBlack) {
                        sibling->right->color = 0;
                        sibling->color = 1;
                        LeftRotate(sibling, sibling->right);
                        sibling = parent->left;
                    }

                    sibling->color = parent->color;
                    parent->color = 0;
                    sibling->left->color = 0;
                    RightRotate(parent, sibling);
                    node = root;
                }
            }
        }

        if (node) node->color = 0;
    }

    void transplant(RBNode<T>* u, RBNode<T>* v) {

        if (u==root) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v) {
            v->parent = u->parent;
        }

    }

    RBNode<T>* getMinimum(RBNode<T>* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    RBNode<T>* getPredecessor(RBNode<T>* node) {
        RBNode<T>* current = node->left;
        while (current && current->right) {
            current = current->right;
        }
        return current;
    }

    RBNode<T>* getSuccessor(RBNode<T>* node) {
        RBNode<T>* current = node->right;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    string output = "";
    void PrintTree() {
        function <void(RBNode<T>* )> dfs = [&](RBNode<T>* current)->void {
            if (current == nullptr) return;
            cout << output;
            cout << current->value << "(" << ((current->color) ? "R" : "B") << ")" << '\n';
            output += "   ";
            dfs(current->left);
            dfs(current->right);
            output.pop_back();
            output.pop_back();
            output.pop_back();
            return;
        };
        cout << '\n';
        dfs(root);
    }
};

int main() {
    RBTree<int> tree;
    tree.Insert(10);
    tree.PrintTree();

    tree.Insert(5);
    tree.PrintTree();

    tree.Insert(15);
    tree.PrintTree();

    tree.Insert(3);
    tree.PrintTree();

    tree.Insert(7);
    tree.PrintTree();

    tree.Insert(13);
    tree.PrintTree();

    tree.Insert(17);
    tree.PrintTree();

    tree.Delete(3);
    tree.PrintTree();

    tree.Delete(5);
    tree.PrintTree();

    tree.Delete(10);
    tree.PrintTree();

    tree.Delete(15);
    tree.PrintTree();



    RBTree<int> rbTree;

    rbTree.Insert(10);
    rbTree.PrintTree();
    rbTree.Insert(15);
    rbTree.PrintTree();
    rbTree.Insert(20);
    rbTree.PrintTree();

    rbTree.Insert(5);
    rbTree.PrintTree();

    rbTree.Insert(1);
    rbTree.PrintTree();



    rbTree.Delete(1);
    rbTree.PrintTree();

    rbTree.Delete(5);
    rbTree.PrintTree();

    rbTree.Delete(15);
    rbTree.PrintTree();

    rbTree.Delete(10);
    rbTree.PrintTree();
    rbTree.Delete(10);
    rbTree.PrintTree();
    rbTree.Delete(5);
    rbTree.PrintTree();
}
