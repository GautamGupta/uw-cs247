/**
 * View class. Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 */

#include "view.h"
#include "model.h"
#include "card.h"
#include <iostream>
#include <cassert>
#include <algorithm>

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

void View::displayCardsOnTable(SuitCards suitCards) {
    cout << "Cards on the table:" << endl;

    // Order matters
    for (int suitNum = CLUB; suitNum < SUIT_COUNT; suitNum++) {
        Suit suit = static_cast<Suit>(suitNum);
        vector<Rank> ranks;

        for (int i = 0; i < suitCards[suit].size(); i++) {
            ranks.push_back(suitCards[suit].at(i)->getRank());
        }
        sort(ranks.begin(), ranks.end());

        switch (suit) {
            case CLUB :
                cout << "Clubs: ";
                break;
            case DIAMOND :
                cout << "Diamonds: ";
                break;
            case HEART :
                cout << "Hearts: ";
                break;
            case SPADE :
                cout << "Spades: ";
                break;
        }

        displayCards(ranks);
    }
}

void View::displayCards(vector<Rank> ranks) {
    for (int i = 0; i < ranks.size(); i++) {
        cout << ranks.at(i) << " ";
    }

    cout << endl;
}
