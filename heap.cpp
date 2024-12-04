
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include "common.cpp"
int type = 1;

class MinHeap{
    vector<Item>v;

public:
    void  insert(Item it) {
        v.push_back(it);
      //  heapify(v.size(),0);
    }
    void del(Item it){
        for(int i =0;i<v.size();i++){
            if(v[i].getItemName()==it.getItemName()&&v[i].getItemprice()==it.getItemprice()){
                v.erase(v.begin()+i);
                break;
            }
        }
        buildheap(type);
    }
    void buildheap(int t ){
        for (int i = ((v.size() / 2)-1 ); i >= 0; i--) {
            heapify(v.size(),i);
        }
    }
   void  heapify(int n,int ind ) {
       if(type==1) {
           // byname
          int l = (2*ind)+1;
          int r = (2*ind )+2;
          int mi = ind;
          if(l<n&&v[l]<v[mi])mi =l;
          if(r<n&&v[r]<v[mi]) mi =r;
          if(mi!=ind){
              swap(v[ind],v[mi]);
              heapify(n,mi);
          }
       }
       else{

int l = (2*ind)+1;
           int r = (2*ind )+2;
           int mi = ind;
           if(l<n&&v[mi]>v[l])mi =l;;
           if(r<n&&v[mi]>v[r]) mi =r;
           if(mi!=ind){
               swap(v[ind],v[mi]);
               heapify(n,mi);
           }

           }
       }

vector<Item> heapsort(int t) {
       type=t;

   vector<Item> sorted;

    buildheap (t);

    for(int i = v.size()-1;i>=0;i--){
       sorted.push_back(v[0]);
        swap(v[0],v[i]);
        heapify(i,0);
}
    return v;
}
    void display(){
        for(auto p :v){
            p.print();
        }
    }

};

class MaxHeap{
    vector<Item>v;
public:

    void  insert(Item it) {
        v.push_back(it);
       // buildheap(type);
    }
    void del(Item it){
        for(int i =0;i<v.size();i++){
            if(v[i].getItemName()==it.getItemName()&&v[i].getItemprice()==it.getItemprice()){
                v.erase(v.begin()+i);
                break;
            }
        }
        buildheap(type);
    }
    void buildheap(int t ){
        for (int i = ((v.size() / 2) - 1); i >= 0; i--) {
            heapify(v.size(),i);
        }
    }
    void  heapify(int n, int ind ) {
        if(type==1) {
            // byname
            int l = (2*ind)+1;
            int r = (2*ind )+2;
            int mi = ind;
            if(l<n&&v[mi]<v[l])mi =l;
            if(r<n&&v[mi]<v[l]) mi =r;
            if(mi!=ind){
                swap(v[ind],v[mi]);
                heapify(n,mi);
            }
        }
        else{

            int l = (2*ind)+1;
            int r = (2*ind )+2;
            int mi = ind;
            if(l<n&&v[l]>v[mi])mi =l;
            if(r<n&&v[r]>v[mi]) mi =r;
            if(mi!=ind){
                swap(v[ind],v[mi]);
                heapify(n,mi);
            }

        }
    }

    vector<Item> heapsort(int t)  {
        vector<Item> sorted;
        type =t;
        buildheap (t);

        for(int i = v.size()-1;i>=0;i--){
sorted.push_back(v[0]);
            swap(v[0],v[i]);
            heapify(i,0);
        }
        return v;
    }
    void display(){
        for(auto p :v){
            p.print();
        }
    }



};
//int main(){
//
//
//
//}



