/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

#include "model.h"
#include "card.h"
#include <vector>
#include <iostream>

using namespace std;

Model::Model() {}

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
    players_.at(playerNum)->addOriginalCard(card);
}

void Model::debug() {
    for (int i = 0; i < 4; i++) {
        cout << "Player " << i << "'s hand" << endl;
        for (int j = 0; j < 13; j++) {
            cout << i << " " << j << " " << *((players_.at(i)->getOriginalCards()).at(j)) << endl;
        }
    }

    cout << startPlayer() << endl;
}
