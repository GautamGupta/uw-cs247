/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

#include "main.h"
#include "model.h"
#include "card.h"
#include "player.h"
#include <vector>
#include <map>

using namespace std;

Model::Model() : startPlayer_(-1) {}

Players Model::players() {
    return players_;
}

int Model::startPlayer() {
    return startPlayer_;
}

tr1::shared_ptr<Player> Model::player(int i) {
    return players().at(i);
}

void Model::startRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player(i)->startRound();
    }
}

void Model::endRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player(i)->endRound();
    }
}

bool Model::isGameOver() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (player(i)->checkEndGame()) {
            return true;
        }
    }
    return false;
}

int Model::lowestScore() {
    int lowestScore = player(0)->calculateScore();
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (player(i)->calculateScore() < lowestScore) {
            lowestScore = player(i) ->calculateScore();
        }
    }
    return lowestScore;
}

Cards Model::getDeck() {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < player(i)->getOriginalCards().size(); j++) {
            cards.push_back(player(i)->getOriginalCards().at(j));
        }
    }

    return cards;
}

Cards Model::getCardsOnTable() {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        cards.insert(cards.end(), player(i)->getPlayedCards().begin(), player(i)->getPlayedCards().end());
    }

    return cards;
}

SuitCards Model::getSuitCardsOnTable() {
    SuitCards suitCards;

    for (int suitNum = CLUB; suitNum < SUIT_COUNT; suitNum++) {
        Suit suit = static_cast<Suit>(suitNum);
        suitCards[suit] = vector< tr1::shared_ptr<Card> >();
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < player(i)->getPlayedCards().size(); j++) {
            tr1::shared_ptr<Card> card = player(i)->getPlayedCards().at(j);
            suitCards[card->getSuit()].push_back(card);
        }
    }

    return suitCards;
}

/**
 * Get legal plays for a player
 * @param  playerNum Index position of player
 */
Cards Model::getLegalPlays(int playerNum) {
    return player(playerNum)->getLegalPlays(getCardsOnTable());
}

void Model::setStartPlayer(int startPlayer) {
    startPlayer_ = startPlayer;
}

/**
 * Add player to our players array
 * @param Player* Pointer to player object
 */
void Model::addPlayer(tr1::shared_ptr<Player> player) {
    players_.push_back(player);
}


/**
 * Replace player to our players array
 * @param int Index to replace
 * @param Player* Pointer to player object
 */
void Model::replacePlayer(int playerNum, tr1::shared_ptr<Player> player) {
    players_[playerNum] = player;
}

/**
 * Add card to player
 */
void Model::addPlayerCard(int playerNum, tr1::shared_ptr<Card> card) {
    player(playerNum)->addCard(card);
}
