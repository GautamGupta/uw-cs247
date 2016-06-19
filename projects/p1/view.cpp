/**
 * View class. Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 */

#include "view.h"
#include "model.h"
#include <iostream>
#include <cassert>

using namespace std;

View::View(Model *m) : model_(m) {}

View::~View() {}

Model* View::model() {
    return model_;
}

char View::inputPlayer(int playerNum) {
    char type;

    cout << "Is player " << playerNum << " a human(h) or a computer(c)?" << endl;
    cin >> type;
    assert ( !cin.fail() );

    return type;
}

void View::startRound(int playerNum) {
    cout << "A new round begins. It’s player " << playerNum << "'s turn to play." << endl;
}
