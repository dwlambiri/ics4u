// Name:
// list.cpp
// List Class - an ordered link list
/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   List.cpp
 *	Course: ICS4U
 *	Date:   Nov 13, 2017
 *
 *	Purpose:This contains a linked list containing city names stored in
 *				apstrings
 *
 *	Usage:  This file is used in a main
 *
 *	Revision History:
 *
 *	Known Issues: No known bugs.
 *
 *****************************************************************************/


#include <iostream>
#include <fstream>
#include "List.h"

using namespace std;

// construct empty list
List::List() :
		head(nullptr), tail(nullptr), length(0) {
		}

// construct list with one node
List::List(apstring city) :
		length(1) {
	head = new Node(city);
	tail = head;
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
	bool removed = false;
	int nodesRemoved = 0;
	if (length == 0)
		return removed;
	//removes nodes by finding out if they exist in the linked list or not.
	for (Node* t = head; t != nullptr; t = t->next) {
		if(t->city == city) {
			cout << "Removing " << city << endl;
			if(t->next) {
				t->next->prev = t->prev;
			}
			else {
				tail = t->prev;
			}
			if(t->prev) {
				t->prev->next = t->next;
			}
			else {
				head = t->next;
			}
			delete t;
			nodesRemoved++;
		}
	}
	length -= nodesRemoved;
	return removed;
}

// add city to list, in alphabetical order
void List::insert(apstring city) {
	Node *newnode = new Node;
    newnode->city = city;
    newnode->next = nullptr;

    if (!head) {
        head = newnode;
        length++;
        return;
    }

    Node *prev = nullptr;
    Node *t = head;
    while (t != nullptr && t->city < city) {
        prev = t;
        t = t->next;
    }
    //If t is the head then we must only set the
    // head to newnode and the previous of the old head
    // to newnode
    //We do not want to operate upon the previous of the head as
    //  it will result in a segmentation fault 11
    if (t == head) {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
        length++;
        return;
    }
    //placing newnode in the linked list
    prev->next = newnode;
    newnode->next = t;
    newnode->prev = prev;
    //the last node will point to a nullptr
    //checking if newnode is the last node
    if (t!= nullptr){
        t->prev = newnode;
    }
    else{
        tail = newnode;
    }
    length++;
}

// free memory of all the nodes in the list
List::~List() {
	if (head) {
		if (head->next) {
			for (Node *t = head->next; t != nullptr; t=t->next) {
				delete t->prev;
			}
		}
		delete tail;
	}
}

// show list of cities
void List::show() {
	for (Node *t = head; t != nullptr; t=t->next)
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
    //fin.ignore(256, '\n');
    //fin.ignore(256, ' ');
	while (getline(fin, name)) {
		//cout << "++" << name << "++" << endl;
		insert(name);
	}
	return true;

}

// save the list to the specified file
bool List::save(apstring filename) {
	cout << "Stub for saving to " << filename << endl;
	ofstream cityFile;
	cityFile.open(filename.c_str());
	for (Node* t = head; t != nullptr; t = t->next) {
		cityFile << t->city << "\n";
	} //end-of-for
	return true;
}
