/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

#include "main.h"
#include "model.h"
#include "card.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

Model::Model() {}

shared_ptr<Player> Model::player(int i) {
    return players_.at(i);
}

SuitCards Model::getCardsOnTable() {
    SuitCards suitCards;

    for (int suitNum = CLUB; suitNum < SUIT_COUNT; suitNum++) {
        Suit suit = static_cast<Suit>(suitNum);
        suitCards[suit] = vector< shared_ptr<Card> >();
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < player(i)->getPlayedCards().size(); j++) {
            shared_ptr<Card> card = player(i)->getPlayedCards().at(j);
            suitCards[card->getSuit()].push_back(card);
        }
    }

    return suitCards;
}

int Model::startPlayer() {
    return startPlayer_;
}

void Model::setStartPlayer(int startPlayer) {
    startPlayer_ = startPlayer;
}

/**
 * Add player to our players array
 * @param Player* Pointer to player object
 */
void Model::addPlayer(shared_ptr<Player> player) {
    players_.push_back(player);
}

/**
 * Add card to player
 */
void Model::addPlayerCard(int playerNum, shared_ptr<Card> card) {
    player(playerNum)->addOriginalCard(card);
}

void Model::debug() {
    for (int i = 0; i < 4; i++) {
        cout << "Player " << i << "'s hand" << endl;
        for (int j = 0; j < 13; j++) {
            cout << i << " " << j << " " << *((player(i)->getOriginalCards()).at(j)) << endl;
        }
    }

    cout << startPlayer() << endl;
}
