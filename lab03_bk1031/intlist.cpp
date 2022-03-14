// intlist.cpp
// Implements class IntList
// Bharat Kathi (5938444) 2/1/22

#include "intlist.h"

#include <iostream>
using std::cout;

// copy constructor
IntList::IntList(const IntList& source) {
    first = 0;
    for (Node* p = source.first; p != NULL; p = p->next) {
        append(p->info);
    }
}

// destructor deletes all nodes
IntList::~IntList() {
    Node* p = first;
    while (p) {
        p = p->next;
        delete first;
        first = p;
    }
    delete p;
    delete first;
}


// return sum of values in list
int IntList::sum() const {
    int sum = 0;
    Node* p = first;
    while (p) {
        sum += p->info;
        p = p->next;
    }
    return sum;
}

// returns true if value is in the list; false if not
bool IntList::contains(int value) const {
    if (count() == 0) return false;
    Node* p = first;
    while (p) {
        if (p->info == value) {
            return true;
        }
        p = p->next;
    }
    return false;
}

// returns maximum value in list, or 0 if empty list
int IntList::max() const {
    if (count() == 0) return 0;
    int max = first->info;
    Node* p = first;
    while (p) {
        if (p->info > max) {
            max = p->info;
        }
        p = p->next;
    }
    return max;
}

// returns average (arithmetic mean) of all values, or
// 0 if list is empty
double IntList::average() const {
    if (count() == 0) return 0.0;
    return (double) sum() / (double) count();
}

// inserts value as new node at beginning of list
void IntList::insertFirst(int value) {
    Node* p = new Node;
    p->info = value;
    p->next = first;
    first = p;
}

//Assignment operator should copy the list from the source
//to this list, deleting/replacing any existing nodes
//IntList& IntList::operator=(const IntList& source) {
//    first = 0;
//    for (Node* p = source.first; p != NULL; p = p->next) {
//        append(p->info);
//    }
//    return *this;
//}


// DO NOT CHANGE ANYTHING BELOW (READ IT THOUGH)

// constructor sets up empty list
IntList::IntList() : first(0) { }


// append value at end of list
void IntList::append(int value) {
    if (first == 0) { // empty list
        first = new Node;
        first->info = value;
        first->next = 0;
    }
    else {
        Node *n = first;
        while (n->next) // not last node yet
            n = n->next;
        n->next = new Node;
        n->next->info = value;
        n->next->next = 0;
    }
}

// print values enclose in [], separated by spaces
void IntList::print() const {
    Node *n = first;
    cout << '[';
    while (n) {
        cout << n->info;
        if (n->next)
            cout << " ";
        n = n->next;
    }
    cout << ']';
}

// return count of values
int IntList::count() const {
    int result = 0;
    Node *n = first;
    while (n) {
        ++result;
        n = n->next;
    }
    return result;
}
