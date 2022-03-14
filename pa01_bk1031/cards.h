//cards.h
//Authors: Bharat Kathi (5938444)
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H

#include "iostream"

using namespace std;

class CardBST {

    public:
        struct Node {
            int info;
            Node *left, *right, * parent;
            // useful constructor:
            Node(int v=0) : info(v), left(0), right(0), parent(0) { }
        };
        Node *root;

        CardBST();                   // constructor
        ~CardBST();                  // destructor
        bool insert(int value);     // insert value; return false if duplicate

        void printInOrder() const;       // print tree data in-order to cout

        bool contains(int value) const;  // true if value is in tree

        int getPredecessor(int value) const;       // returns the predecessor value of the given value or 0 if there is none
        int getSuccessor(int value) const;         // returns the successor value of the given value or 0 if there is none
        bool remove(int value);                    // deletes the Node containing the given value from the tree

        int cardToInt(string card) const;
        string intToCard(int num) const;

        int gameTurnForward(string name, Node *n, CardBST *other);
        int gameTurnReverse(string name, Node *n, CardBST *other);

    private:

        // recursive utility functions for use by public methods above
        Node* getNodeFor(int value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
        void clear(Node *n); // for destructor
        bool insert(int value, Node *n); // note overloading names for simplicity
        void printInOrder(Node *n) const;

        // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
        Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
        Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value
};

#endif