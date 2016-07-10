/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

#include "main.h"
#include "model.h"
#include "card.h"
#include "player.h"
#include "humanplayer.h"
#include <vector>
#include <map>

using namespace std;

Model::Model() : startPlayer_(-1) {
    // Initialize 4 humans
    for (int i = 0; i < NUM_PLAYERS; i++) {
        shared_ptr<Player> humanPlayer(new HumanPlayer());
        addPlayer(humanPlayer);
    }
}

Players Model::players() {
    return players_;
}

int Model::startPlayer() {
    return startPlayer_;
}

shared_ptr<Player> Model::player(int i) {
    return players().at(i);
}

/**
 * Start round for every player
 */
void Model::startRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player(i)->startRound();
    }
}

/**
 * Calculate scores for every player
 */
void Model::endRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player(i)->endRound();
    }
}

/**
 * Check if player has > 80 pts
 */
bool Model::isGameOver() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (player(i)->checkEndGame()) {
            return true;
        }
    }
    return false;
}

/**
 * See what's the lowest score in the game
 */
int Model::lowestScore() {
    int lowestScore = player(0)->calculateScore();
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (player(i)->calculateScore() < lowestScore) {
            lowestScore = player(i) ->calculateScore();
        }
    }
    return lowestScore;
}

/**
 * Add all cards assigned to players to an array and return (in order)
 */
Cards Model::getDeck() {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < player(i)->getOriginalCards().size(); j++) {
            cards.push_back(player(i)->getOriginalCards().at(j));
        }
    }

    return cards;
}

/**
 * Get all the played cards for the round
 */
Cards Model::getCardsOnTable() {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        cards.insert(cards.end(), player(i)->getPlayedCards().begin(), player(i)->getPlayedCards().end());
    }

    return cards;
}

/**
 * Get a hashmap of (Suit -> Vector of cards of suit) played for the round
 */
SuitCards Model::getSuitCardsOnTable() {
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

/**
 * Get legal plays for a player. We need to supply cards on table.
 * @param  playerNum Index position of player
 */
Cards Model::getLegalPlays(int playerNum) {
    return player(playerNum)->getLegalPlays(getCardsOnTable());
}

/**
 * Set start to the player who has 7S
 */
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
 * Replace player to our players array
 * @param int Index to replace
 * @param Player* Pointer to player object
 */
void Model::replacePlayer(int playerNum, shared_ptr<Player> player) {
    players_[playerNum] = player;
}

/**
 * Add card to player
 */
void Model::addPlayerCard(int playerNum, shared_ptr<Card> card) {
    player(playerNum)->addCard(card);
}
