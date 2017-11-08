// Name:
// list.cpp
// List Class - an ordered link list

#include <iostream>
#include <fstream>
#include "List.h"

using namespace std;

// construct empty list
List::List() : head(nullptr), length(0) {
	 head = NULL;
	 length = 0;
}

// construct list with one node
List::List(apstring city) : head(nullptr), length(1) {
	 head = new Node;
	 head->city = city;
	 head->next = NULL;
	 length = 1;
}

// return true if list is empty
bool List::empty() {
	return (length == 0);
}

// return size of List
int List::size() {
	return length;
}

// remove city from list, return false if not in list.
// (optional enhancement remove all instances of that city)
bool List::remove(apstring city) {
   cout << "Stub for removing " << city << endl;

}

// add city to list, in alphabetical order
void List::insert(apstring city) {
    cout << "Stub for adding " << city << endl;

}

// free memory of all the nodes in the list
List::~List() {

}

// show list of cities
void List::show() {
    for (Node *t = head; t; t=t->next)
        cout << t->city << endl;
    cout << endl;
}

// reads a list of cities in to an empty list

bool List::load(apstring filename) {
    Node *back = head;
    apstring name;

    ifstream fin(filename.c_str());
    if (!fin) {
        cout << "Unable to open " << filename << endl;
        return false;
    }
    // TDB  allow loading to existing list (easy once insert function works)
    if (!empty()) {
        cout << "Only can load to empty list" << endl;
        return false;
    }
    while (getline(fin, name)) {
      //  cout << "Adding... " <<  name << endl;
        Node *newnode = new Node;
        newnode->city = name;
        newnode->next = NULL;
        if (back)
            back->next = newnode;
        else
            head = newnode;
        back = newnode;
        newnode = back;
        length++;
    }
    return true;

}

// save the list to the specified file
bool List::save(apstring filename) {
   cout << "Stub for saving to " << filename << endl;
}
