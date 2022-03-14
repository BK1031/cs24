// intbst.cpp
// Implements class IntBST
// Bharat Kathi (593844)

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Node(value);
        return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	    return false;
    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        else {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right)
            return insert(value, n->right);
        else {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr) return 0;
    return (n->info + sum(n->left) + sum(n->right));
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr) return 0;
    return (1 + count(n->right) + count(n->left));
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (n == nullptr) return NULL;
    if (n->info == value) return n;
    Node* leftSearch = getNodeFor(value, n->left);
    if (leftSearch != NULL) return leftSearch;
    Node* rightSearch = getNodeFor(value, n->right);
    if (rightSearch != NULL) return rightSearch;
    return NULL;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (getNodeFor(value, root) == NULL) return false;
    return true;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const {
    Node* start = getNodeFor(value, root);
    if (start == NULL) return NULL;
    if (start->left != NULL) {
        start = start->left;
        while (start->right != NULL) {
            start = start->right;
        }
        return start;
    }
    else {
        while (start->parent != NULL) {
            if (start->info < value) {
                return start;
            }
            start = start->parent;
        }
        return NULL;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
    Node* result = getPredecessorNode(value);
    if (result != NULL) return result->info;
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* start = getNodeFor(value, root);
    if (start == NULL) return NULL;
    if (start->right != NULL) {
        start = start->right;
        while (start->left != NULL) {
            start = start->left;
        }
        return start;
    }
    else {
        while (start->parent != NULL) {
            if (start->info > value) {
                return start;
            }
            start = start->parent;
        }
        return NULL;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const {
    Node* result = getSuccessorNode(value);
    if (result != NULL) return result->info;
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value) {
    Node* current = getNodeFor(value, root);
    if (current == NULL) return false;
    if (current->left == NULL && current->right == NULL) {
        // Node is a leaf
        if (current->parent == NULL) {
            root = NULL;
            current = NULL;
        }
        else if (current->parent->left == current) {
            current->parent->left = NULL;
            current = NULL;
        }
        else {
            current->parent->right = NULL;
            current = NULL;
        }
    }
    else if (current->right == NULL) {
        // Node only has left child
        if (current->parent == NULL) {
            root = current->left;
            current->left->parent = NULL;
            current = NULL;
        }
        else if (current->parent->left == current) {
            current->parent->left = current->left;
            current->left->parent = current->parent;
            current = NULL;
        }
        else {
            current->parent->right = current->left;
            current->left->parent = current->parent;
            current = NULL;
        }
    }
    else if (current->left == NULL) {
        // Node only has right child
        if (current->parent == NULL) {
            root = current->right;
            current->right->parent = NULL;
            current = NULL;
        }
        else if (current->parent->left == current) {
            current->parent->left = current->right;
            current->right->parent = NULL;
            current = NULL;
        }
        else {
            current->parent->right = current->right;
            current->right->parent = current->parent;
            current = NULL;
        }
    }
    else {
        // Node has both left and right children
        Node* successor = getSuccessorNode(value);
        remove(successor->info);
        current->info = successor->info;
    }
    return true;
}
