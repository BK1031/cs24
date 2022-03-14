#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int main(int argv, char** argc) {

    CardBST alice, bob;

    if (argv < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1 (argc[1]);
    ifstream cardFile2 (argc[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()){
    cout << "Could not open file " << argc[2];
    return 1;
    }

    // Read each file
    while (getline (cardFile1, line) && (line.length() > 0)) {
        int num = alice.cardToInt(line);
        alice.insert(num);
    }
    cardFile1.close();


    while (getline (cardFile2, line) && (line.length() > 0)) {
        int num = bob.cardToInt(line);
        bob.insert(num);
    }
    cardFile2.close();


    while (true) {
        int card = alice.gameTurnForward("Alice", alice.root, &bob);
        if (card == 0) break;
        alice.remove(card);

        card = bob.gameTurnReverse("Bob", bob.root, &alice);
        if (card == 0) break;
        bob.remove(card);
    }

    cout << endl;
    cout << "Alice's cards:" << endl;
    alice.printInOrder();
    cout << endl;
    cout << "Bob's cards:" << endl;
    bob.printInOrder();
    return 0;
}