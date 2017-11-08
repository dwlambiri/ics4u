#ifndef LIST_H
#define LIST_H
// Name:
// list.h
// List Class - an ordered link list

using namespace std;
#include "apstring.h"
struct Node {
    apstring city;
    Node *next;
};

class List {
	private:
		int length;
		Node *head;
    public:
	    List();
        List(apstring);
		bool empty();
		int size();
	    void insert(apstring);
		bool remove(apstring);
		void show();
		// enrichment, store in doubly linked list and display in reverse order
		//void showReverse();
		bool load(apstring filename);
		bool save(apstring filename);
		~List();
};
#endif
