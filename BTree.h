#include <iostream>
#include <vector>
#include <functional>
#include <queue>

#ifndef ADVANCED_DATA_STRUCTURES_BTREE_H
#define ADVANCED_DATA_STRUCTURES_BTREE_H
using namespace std;

// Author Malak Hisham
// date 9/12/2024
template<class T, int order>
 struct BTreeNode{
    BTreeNode* parent;

 public:
    vector<T> keys;
    bool leaf;
     vector<BTreeNode<T,order>*> childrens;
    BTreeNode(){
        leaf = false;
        parent = nullptr;
        keys.resize(0);
        childrens.resize(0);
    }

     ~BTreeNode() {
         for (auto *child : childrens) {
             delete child; // Recursively delete child nodes
         }
         childrens.clear(); // Clear the vector to release resources
     }

};

template<class T, int order>
class BTree{
    BTreeNode <T,order> * root ;
public:
    BTree(){
        root = nullptr;
    }
    void Insert(T val){
        BTreeNode<T,order>* Mynode = search(val);
        T extract = val;

        while(Mynode!= nullptr&&Mynode->keys.size()==order-1) {
            vector<T> sorted = Mynode->keys;

            sorted.push_back(extract);
            sort(sorted.begin(),sorted.end());
            if(sorted.size()==order) {
                extract = sorted[order / 2];

                sorted.erase(find(sorted.begin(),sorted.end(),extract));

                Mynode->keys = sorted;
                if(Mynode->parent!= nullptr){
                    int i =0;

                    for(auto child : Mynode->parent->childrens){
                        if(child==Mynode){
                            split(Mynode->parent,order/2 ,i);
                        }
                        i++;
                    }
                }
                else {
                    BTreeNode<T, order> *newRoot = new BTreeNode<T, order>;
                    newRoot->childrens.push_back(Mynode);
                    Mynode->parent = newRoot;
                    root = newRoot;
                    split(Mynode->parent, order/2 );

                }
            }else{
                Mynode->keys = sorted;
                break;
            }

            Mynode = Mynode->parent;
        }
        if(Mynode== nullptr) {
            BTreeNode<T, order> *newRoot = new BTreeNode<T, order>;
            if (root == nullptr)
                newRoot->leaf = 1;
            newRoot->keys.push_back(extract);
            Mynode = newRoot;
            root = newRoot;
        }
        else{

            Mynode->keys.push_back(extract);
            sort(Mynode->keys.begin(),Mynode->keys.end());

        }


    }
    // node splitted its node added to previous and back of neghibors
    BTreeNode <T,order>*  search(T val){
        BTreeNode<T,order>* mypointer = root;
        bool found =0;
        while(!found&&mypointer!= nullptr&&!mypointer->leaf){
                for(int i =0;i<mypointer-> keys.size()  ;i++){
                    if(val<mypointer->keys[i]){
                        if(!mypointer->childrens.empty()&&mypointer->childrens[i]!= nullptr) {
                            mypointer = mypointer->childrens[i];

                            found = 1;
                            break;
                        }
                        else {
                            found =1;
                            break;
                        }

                    }


        }

                if(!found&&!mypointer->childrens.empty())mypointer = mypointer->childrens.back();
        }


        return mypointer;
    }

    void split(BTreeNode<T,order> * currentNode,T index,int indexOfchildToparent = 0) {
        // parent of splitted
        // make new child for it
        // get index of child from the parent
       BTreeNode<T,order> *  newnode = new BTreeNode<T,order> ();

       for(int i =index;i<currentNode->childrens[indexOfchildToparent]->keys.size();i++){
           newnode->keys.push_back(currentNode->childrens[indexOfchildToparent]->keys[i]);

           if(!currentNode->childrens[indexOfchildToparent]->leaf)
               newnode->childrens.push_back(currentNode->childrens[indexOfchildToparent]->childrens[index + 1]);

               currentNode->childrens[indexOfchildToparent]->keys.erase(
                       currentNode->childrens[indexOfchildToparent]->keys.begin() + index);

           if(!currentNode->childrens[indexOfchildToparent]->leaf)
               currentNode->childrens[indexOfchildToparent]->childrens.erase( currentNode->childrens[indexOfchildToparent]->childrens.begin()+index+1);
           i--;
       }
       newnode->parent = currentNode;
        if(!currentNode->childrens[indexOfchildToparent]->leaf)
            newnode->childrens.push_back(currentNode->childrens[indexOfchildToparent]->childrens.back());
        if(currentNode->childrens.back()->leaf)
            newnode->leaf = 1;
        currentNode->childrens.insert(currentNode->childrens.begin()+indexOfchildToparent+1,newnode);
        if(!currentNode->childrens[indexOfchildToparent]->leaf)
            currentNode->childrens[indexOfchildToparent]->childrens.pop_back();
      // currentNode->childrens[indexOfchildToparent]->childrens.push_back(nullptr);


    }


    void Print(){
                string output="";
        function <string(BTreeNode<T,order>* )> dfs = [&](BTreeNode<T,order> * current)->string{
            if(current== nullptr)return"";
                int u = current->keys.size()-1;
            for(int i =0;i<current->keys.size();i++) {
                cout<< current->keys[i];
                if(u)u--,cout<<'.';

            }
            output+="  ";



            if(!current->leaf) {
                  //  cout<<"\n";
                for (int i = 0; i < current->childrens.size(); i++) {

                    //cout<<i<<' ';
                    if (i < current->childrens.size() && current->childrens[i] != nullptr) {
                        cout<<'\n'<<output;
                        dfs(current->childrens[i]);
                        output.pop_back();
                        output.pop_back();
                    }
                }
            }
            return output;
        };

       cout<< dfs(root);
    }

    ~BTree() {
        delete root; // Deleting the root will trigger recursive deletion of all children
        root = nullptr;
    }


};


#endif //ADVANCED_DATA_STRUCTURES_BTREE_H
