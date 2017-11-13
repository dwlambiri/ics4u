// Name:
// list.cpp
// List Class - an ordered link list

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
	cout << "Stub for removing " << city << endl;
	for (Node* t = head; t != nullptr; t = t->next) {
		if(t->city == city) {
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
	cout << "Stub for adding " << city << endl;
	Node* p = new Node(city);
	p->prev = tail;

	if (tail != nullptr) {
		tail->next = p;
	}
	tail = p;

	if (head == nullptr) {
		head = p;
	}

	length++;
	//cout << "LALALALA" <<endl;
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

	while (getline(fin, name)) {
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
