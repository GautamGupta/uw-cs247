/**
 * View class. Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 */

#include "main.h"
#include "view.h"
#include "model.h"
#include "card.h"
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

View::View() {}

View::~View() {}

char View::inputPlayer(int playerNum) {
    char type;

    cout << "Is player " << (playerNum + 1) << " a human(h) or a computer(c)?" << endl;
    cin >> type;
    assert ( !cin.fail() );

    return type;
}

void View::startRound(int playerNum) {
    cout << "A new round begins. It’s player " << (playerNum + 1) << "'s turn to play." << endl;
}

void View::endRound(int playerNum, Player player) {
    cout << "Player " << (playerNum + 1) << "'s discards: ";
    displayCards(player.getDiscardedCards());

    cout << "Player " << (playerNum + 1) << "'s score: "
        << player.getPreviousScore() << " + " << player.getScore()
        << " = " << (player.getPreviousScore() + player.getScore()) << endl;
}

void View::displayDiscards(Cards cards) {
    displayCards(cards);
}

void View::displayCardsOnTable(SuitCards suitCards) {
    cout << "Cards on the table:" << endl;

    // Order matters
    for (int suitNum = CLUB; suitNum < SUIT_COUNT; suitNum++) {
        Suit suit = static_cast<Suit>(suitNum);
        vector<int> ranks;

        for (int i = 0; i < suitCards[suit].size(); i++) {
            ranks.push_back((int) suitCards[suit].at(i)->getRank()); // Ace is 0
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

            default :
                break;
        }

        displayCards(ranks);
    }
}

void View::displayHand(Cards cards) {
    cout << "Your hand: ";
    displayCards(cards);
}

void View::displayLegalPlays(Cards cards) {
    cout << "Legal plays: ";
    displayCards(cards);
}

void View::displayPlayCard(int playerNum, Card card) {
    cout << "Player " << (playerNum + 1) << " plays " << card << "." << endl;
}

void View::errorPlayCard() {
    cout << "This is not a legal play." << endl;
}

void View::displayDiscardCard(int playerNum, Card card) {
    cout << "Player " << (playerNum + 1) << " discards " << card << "." << endl;
}

void View::errorDiscardCard() {
    cout << "You have a legal play. You may not discard." << endl;
}

void View::displayRageQuit(int playerNum) {
    cout << "Player " << (playerNum + 1) << " ragequits. A computer will now take over." << endl;
}

void View::displayCards(vector<int> ranks) {
    for (int i = 0; i < ranks.size(); i++) {
        cout << Card::getDisplayRank(ranks.at(i)) << " ";
    }

    cout << endl;
}

void View::displayCards(Cards cards) {
    for (int i = 0; i < cards.size(); i++) {
        cout << *cards.at(i);

        // Newline at the end of 13 cards (mainly for deck) / end of list
        if ((i+1) % CARDS_PER_PLAYER == 0 || (i+1) == cards.size()) {
            cout << endl;
        } else {
            cout << " ";
        }
    }

    // Next line if no cards
    if (cards.size() == 0) {
        cout << endl;
    }
}

void View::displayVictory(int playerNum) {
    cout << "Player " << (playerNum + 1) << " wins!" << endl;
}
