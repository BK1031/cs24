//cards.cpp
//Authors: Bharat Kathi (5938444)
//Implementation of the classes defined in cards.h

#include "cards.h"

using namespace std;

// constructor sets up empty tree
CardBST::CardBST() : root(0) { }

// destructor deletes all nodes
CardBST::~CardBST() {
    clear(root);
}

// recursive helper for destructor
void CardBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool CardBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Node(value);
        return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool CardBST::insert(int value, Node *n) {
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

// print tree data in-order, with helper
void CardBST::printInOrder() const {
    printInOrder(root);
}
void CardBST::printInOrder(Node *n) const {
    if (n == nullptr) return;
    printInOrder(n->left);
    cout << intToCard(n->info) << endl;
    printInOrder(n->right);
}

CardBST::Node* CardBST::getNodeFor(int value, Node* n) const {
    if (n == nullptr) return NULL;
    if (n->info == value) return n;
    Node* leftSearch = getNodeFor(value, n->left);
    if (leftSearch != NULL) return leftSearch;
    Node* rightSearch = getNodeFor(value, n->right);
    if (rightSearch != NULL) return rightSearch;
    return NULL;
}

// returns true if value is in the tree; false if not
bool CardBST::contains(int value) const {
    if (getNodeFor(value, root) == NULL) return false;
    return true;
}

int CardBST::cardToInt(string card) const {
    int value = 0;
    char suite = card[0];

    switch (suite) {
        case 'c': value += 100; break;
        case 'd': value += 200; break;
        case 's': value += 300; break;
        case 'h': value += 400; break;
    }

    if (card[2] == 'a') value += 1;
    else if (card[2] == '1') value += 10;
    else if (card[2] == 'j') value += 11;
    else if (card[2] == 'q') value += 12;
    else if (card[2] == 'k') value += 13;
    else value += atoi(&card[2]);

    return value;
}

string CardBST::intToCard(int num) const {
    string card = "";
    int suite = num / 100;

    switch (suite) {
        case 1: card += "c"; break;
        case 2: card += "d"; break;
        case 3: card += "s"; break;
        case 4: card += "h"; break;
    }

    card += " ";
    num -= suite*100;

    if (num == 1) card += "a";
    else if (num == 11) card += "j";
    else if (num == 12) card += "q";
    else if (num == 13) card += "k";
    else card += to_string(num);

    return card;
}

int CardBST::gameTurnForward(string turn, Node *n, CardBST *other) {
    // Searches through current bst in order and removes any values found from other, returns true if values were removed
    int removed = 0;
    if (n == nullptr) return 0;

    removed = gameTurnForward(turn, n->left, other);

    if (removed == 0) {
        bool contains = other->contains(n->info);
        if (contains) {
            other->remove(n->info);
            cout << turn << " picked matching card " << intToCard(n->info) << endl;
            return n->info;
        }
        removed = gameTurnForward(turn, n->right, other);
    }
    return removed;
}

int CardBST::gameTurnReverse(string turn, Node *n, CardBST *other) {
    // Searches through current bst in reverse order and removes any values found from other, returns true if values were removed
    int removed = 0;
    if (n == nullptr) return 0;

    removed = gameTurnReverse(turn, n->right, other);

    if (removed == 0) {
        bool contains = other->contains(n->info);
        if (contains) {
            other->remove(n->info);
            cout << turn << " picked matching card " << intToCard(n->info) << endl;
            return n->info;
        }
        removed = gameTurnReverse(turn, n->left, other);
    }
    return removed;
}

// returns the Node containing the predecessor of the given value
CardBST::Node* CardBST::getPredecessorNode(int value) const {
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
int CardBST::getPredecessor(int value) const {
    Node* result = getPredecessorNode(value);
    if (result != NULL) return result->info;
    return 0;
}

// returns the Node containing the successor of the given value
CardBST::Node* CardBST::getSuccessorNode(int value) const {
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
int CardBST::getSuccessor(int value) const {
    Node* result = getSuccessorNode(value);
    if (result != NULL) return result->info;
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool CardBST::remove(int value){
    Node* n = getNodeFor(value, root);
    if (!n) return false;

    //Case 1: Remove leaf
    if ( !n->left && !n->right ) {
        if (n->parent == NULL) {
            root = NULL;
            n = NULL;
        }
        else if (n->parent->left == n) {
            n->parent->left = NULL;
            n = NULL;
        }
        else {
            n->parent->right = NULL;
            n = NULL;
        }
    }

        //Case 2: Remove node with only left child
    else if ( n->left && !n->right ) {
        if (n->parent == NULL) {
            root = n->left;
            n->left->parent = NULL;
            n = NULL;
        }
        else if (n->parent->left == n) {
            n->parent->left = n->left;
            n->left->parent = n->parent;
            n = NULL;
        }
        else {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            n = NULL;
        }
    }
        //Case 3: Remove node with only right child
    else if ( !n->left && n->right ) {
        if (n->parent == NULL) {
            root = n->right;
            n->right->parent = NULL;
            n = NULL;
        }
        else if (n->parent->left == n) {
            n->parent->left = n->right;
            n->right->parent = n->parent;
            n = NULL;
        }
        else {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            n = NULL;
        }
    }
        //Case 4: Remove node with two children
    else {
        Node *suc = getSuccessorNode(value);
        int sucInfo = suc->info;
        remove(sucInfo);
        n->info = sucInfo;
    }
    return true;
}