#include <iostream>
#include "Full AVL Tree.cpp"
#include "NadaAhmed.cpp"
#include "heap.cpp"
#include "read.cpp"
int main(){


    cout<<"please choose data type you want to use from to 3: \n1. Binary Search Tree\n2. AVL tree\n3. Heap\n";

    int t;
    cin>>t;
    vector<Item> v = readItems("input");
    if(t==1) {
        for(auto h :v)insert(h);
        cout << "Choose an operation to do on AVL Tree (enter from 1 to 8):" << endl;
        cout << "1. Add item " << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Display items normally" << endl;
        cout << "4. Display all items sorted by name ascending" << endl;
        cout << "5. Display all items sorted by name descending" << endl;
        cout << "6. Display all items sorted by price descending" << endl;
        cout << "7. Display all items sorted by price descending" << endl;
        cout << "8. Exit" << endl;

        int choice;
        do {
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string name, category;
                    int price;
                    cout << "Enter Item Name: ";
                    cin >> name;
                    cout << "Enter Category: ";
                    cin >> category;
                    cout << "Enter Price: ";
                    cin >> price;
                    Item newItem(name, category, price);
                    insert(newItem);
                    break;
                }
                case 2: {
                    string name;
                    cout << "Enter Item Name to remove: ";
                    cin >> name;
                    Item remove_item(name, "", 0);
                    delete_item(remove_item);
                    break;
                }
                case 3: {
                    cout << "Displaying items:" << endl;
                    for(auto k:v)k.print();
                    break;
                }
                case 4: {
                    cout << "Displaying items sorted by name ascending:" << endl;
                    display_name_as();
                    break;
                }
                case 5: {
                    cout << "Displaying all items sorted by name descending:" << endl;
                    display_name_ds();
                    break;
                }
                case 6: {
                    cout << "Displaying items sorted by price ascending:" << endl;
                    display_price_as();
                    break;
                }
                case 7: {
                    cout << "Displaying all items sorted by price descending:" << endl;
                    display_price_des();
                    break;
                }
                case 8: {
                    cout << "Exit" << endl;
                    break;
                }
                default:
                    cout << "Invalid choice. try again." << endl;
                    break;
            }
        } while(choice!= 6);
    }
        else if(t==2) {
        // AvL Tree
        cout << "Choose an operation to do on AVL Tree (enter from 1 to 8):" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Display items normally" << endl;
        cout << "4. Display all items sorted by name ascending" << endl;
        cout << "5. Display all items sorted by name descending" << endl;
        cout << "6. Display all items sorted by price ascending" << endl;
        cout << "7. Display all items sorted by price descending" << endl;
        cout << "8. Exit" << endl;

        AVLTree AvlTree;
        for (auto h: v)AvlTree.add(h);
        int choice;
        do {
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string name, category;
                    int price;
                    cout << "Enter Item Name: ";
                    cin >> name;
                    cout << "Enter Category: ";
                    cin >> category;
                    cout << "Enter Price: ";
                    cin >> price;
                    Item newItem(name, category, price);
                    AvlTree.add(newItem);
                    break;
                }
                case 2: {
                    string name;
                    cout << "Enter Item Name to remove: ";
                    cin >> name;
                    Item remove_item(name, "", 0);
                    AvlTree.del(remove_item);
                    break;
                }
                case 3: {
                    cout << "Displaying items:" << endl;
                    AvlTree.display_normally();
                    break;
                }
                case 4: {
                    cout << "Displaying items sorted by name ascending:" << endl;
                    AvlTree.display_Ascending_by_name();
                    break;
                }
                case 5: {
                    cout << "Displaying items sorted by name descending:" << endl;
                    AvlTree.display_Descending_by_name();
                    break;
                }
                case 6: {
                    cout << "Displaying items sorted by price ascending:" << endl;
                    AvlTree.display_Ascending_by_price();
                    break;
                }
                case 7: {
                    cout << "Displaying items sorted by price descending:" << endl;
                    AvlTree.display_Descending_by_price();
                    break;
                }
                default:
                    cout << "Invalid choice. Try again." << endl;
                    break;
            }
        } while (choice != 8);
    }
        else if(t==3) {
        cout << "Choose an operation to do on AVL Tree (enter from 1 to 8):" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Display items normally" << endl;
        cout << "4. Display all items sorted by name ascending" << endl;
        cout << "5. Display all items sorted by name descending" << endl;
        cout << "6. Display all items sorted by price ascending" << endl;
        cout << "7. Display all items sorted by price descending" << endl;
        cout << "8. Exit" << endl;

        vector<Item> temp;
        MinHeap mheap;
        MaxHeap mxheap;
        for (auto h: v)mheap.insert(h);
        for (auto h: v)mxheap.insert(h);
        vector<Item> v1 = mheap.heapsort(0);// byprice  descending
        vector<Item> v2 = mheap.heapsort(1);//by name descending

        vector<Item> v3 = mxheap.heapsort(0);//by price ascending
        vector<Item> v4 = mxheap.heapsort(1);//by name ascending
int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, category;
                int price;
                cout << "Enter Item Name: ";
                cin >> name;
                cout << "Enter Category: ";
                cin >> category;
                cout << "Enter Price: ";
                cin >> price;
                Item newItem(name, category, price);
                mheap.insert(newItem);
                mxheap.insert(newItem);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Item Name to remove: ";
                cin >> name;
                Item remove_item(name, "", 0);
                mheap.del(remove_item);
                mxheap.del(remove_item);
                break;
            }
            case 3: {
                cout << "Displaying items:" << endl;
                for (auto j :v)j.print();
                break;
            }
            case 4: {
                cout << "Displaying items sorted by name ascending:" << endl;
                for (auto j :v4)j.print();
                break;
            }
            case 5: {
                cout << "Displaying items sorted by name descending:" << endl;
                for (auto j :v2)j.print();
                break;
            }
            case 6: {
                cout << "Displaying items sorted by price ascending:" << endl;
                for (auto j :v3)j.print();
                break;
            }
            case 7: {
                cout << "Displaying items sorted by price descending:" << endl;
                for (auto j :v1)j.print();
                break;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }


}