#include <fstream>
#include <iostream>
#include <string>
#pragma once
#include "common.cpp"
vector<Item> readItems(string s){
    vector<Item> v;
    int n;
    string h ;
    ifstream input(s+".txt");
input >>h;
n = stoi(h);
//cout<<n;
input.ignore();
while(n--){

    string name;
    string category;
    int pri;
    string pre;
    getline(input,name);
    getline(input,category);
    getline(input,pre);
    // input>>name>>category>>pre;
    // cout<<name<<category<<pre<<'\n';

     pri = stoi(pre);


    Item it (name,category,pri);

v.push_back( it);
}
    return v;
}
