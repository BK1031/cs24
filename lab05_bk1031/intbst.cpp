// intbst.cpp
// Implements class IntBST
// Bharat Kathi (593844)

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
template <class T>
IntBST<T>::IntBST() : root(0) { }

// destructor deletes all nodes
template <class T>
IntBST<T>::~IntBST() {
    clear(root);
}

// recursive helper for destructor
template <class T>
void IntBST<T>::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
template <class T>
bool IntBST<T>::insert(T value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Node(value);
        return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
template <class T>
bool IntBST<T>::insert(T value, Node *n) {
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
template <class T>
void IntBST<T>::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
template <class T>
void IntBST<T>::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
template <class T>
void IntBST<T>::printInOrder() const {
    printInOrder(root);
}

template <class T>
void IntBST<T>::printInOrder(Node *n) const {
    if (n == nullptr) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
template <class T>
void IntBST<T>::printPostOrder() const {
    printPostOrder(root);
}

template <class T>
void IntBST<T>::printPostOrder(Node *n) const {
    if (n == nullptr) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
template <class T>
int IntBST<T>::sum() const {
    return sum(root);
}

// recursive helper for sum
template <class T>
int IntBST<T>::sum(Node *n) const {
    if (n == nullptr) return 0;
    return (n->info + sum(n->left) + sum(n->right));
}

// return count of values
template <class T>
int IntBST<T>::count() const {
    return count(root);
}

// recursive helper for count
template <class T>
int IntBST<T>::count(Node *n) const {
    if (n == nullptr) return 0;
    return (1 + count(n->right) + count(n->left));
}

// IMPLEMENT THIS FIRST: returns the node for a given value or nullptr if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
template <class T>
typename IntBST<T>::Node* IntBST<T>::getNodeFor(T value, Node* n) const {
    if (n == nullptr) return nullptr;
    if (n->info == value) return n;
    Node* leftSearch = getNodeFor(value, n->left);
    if (leftSearch != nullptr) return leftSearch;
    Node* rightSearch = getNodeFor(value, n->right);
    if (rightSearch != nullptr) return rightSearch;
    return nullptr;
}

// returns true if value is in the tree; false if not
template <class T>
bool IntBST<T>::contains(T value) const {
    if (getNodeFor(value, root) == nullptr) return false;
    return true;
}

// returns the Node containing the predecessor of the given value
template <class T>
typename IntBST<T>::Node* IntBST<T>::getPredecessorNode(T value) const {
    Node* start = getNodeFor(value, root);
    if (start == nullptr) return nullptr;
    if (start->left != nullptr) {
        start = start->left;
        while (start->right != nullptr) {
            start = start->right;
        }
        return start;
    }
    else {
        while (start->parent != nullptr) {
            if (start->info < value) {
                return start;
            }
            start = start->parent;
        }
        return nullptr;
    }
}

// returns the predecessor value of the given value or 0 if there is none
template <class T>
T IntBST<T>::getPredecessor(T value) const {
    Node* result = getPredecessorNode(value);
    if (result != nullptr) return result->info;
    return 0;
}

// returns the Node containing the successor of the given value
template <class T>
typename IntBST<T>::Node* IntBST<T>::getSuccessorNode(T value) const {
    Node* start = getNodeFor(value, root);
    if (start == nullptr) return nullptr;
    if (start->right != nullptr) {
        start = start->right;
        while (start->left != nullptr) {
            start = start->left;
        }
        return start;
    }
    else {
        while (start->parent != nullptr) {
            if (start->info > value) {
                return start;
            }
            start = start->parent;
        }
        return nullptr;
    }
}

// returns the successor value of the given value or 0 if there is none
template <class T>
T IntBST<T>::getSuccessor(T value) const {
    Node* result = getSuccessorNode(value);
    if (result != nullptr) return result->info;
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template <class T>
bool IntBST<T>::remove(T value) {
    Node* current = getNodeFor(value, root);
    if (current == nullptr) return false;
    if (current->left == nullptr && current->right == nullptr) {
        // Node is a leaf
        if (current->parent == nullptr) {
            root = nullptr;
            current = nullptr;
        }
        else if (current->parent->left == current) {
            current->parent->left = nullptr;
            current = nullptr;
        }
        else {
            current->parent->right = nullptr;
            current = nullptr;
        }
    }
    else if (current->right == nullptr) {
        // Node only has left child
        if (current->parent == nullptr) {
            root = current->left;
            current->left->parent = nullptr;
            current = nullptr;
        }
        else if (current->parent->left == current) {
            current->parent->left = current->left;
            current->left->parent = current->parent;
            current = nullptr;
        }
        else {
            current->parent->right = current->left;
            current->left->parent = current->parent;
            current = nullptr;
        }
    }
    else if (current->left == nullptr) {
        // Node only has right child
        if (current->parent == nullptr) {
            root = current->right;
            current->right->parent = nullptr;
            current = nullptr;
        }
        else if (current->parent->left == current) {
            current->parent->left = current->right;
            current->right->parent = nullptr;
            current = nullptr;
        }
        else {
            current->parent->right = current->right;
            current->right->parent = current->parent;
            current = nullptr;
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
