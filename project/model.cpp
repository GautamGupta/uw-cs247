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

Model::Model() : currentPlayer_(-1), numPlays_(0) {
    // Initialize 4 humans
    for (int i = 0; i < NUM_PLAYERS; i++) {
        shared_ptr<Player> humanPlayer(new HumanPlayer());
        players_.push_back(humanPlayer);
    }
}

Players Model::players() {
    return players_;
}

int Model::currentPlayer() {
    return currentPlayer_;
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
    notify();
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
 * Check if 52 cards have been played / discarded in the round
 * ie. if round is over
 */
bool Model::isRoundOver() {
    return numPlays_ == NUM_CARDS;
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
 * Check if a card was played already
 */
bool Model::cardWasPlayed(shared_ptr<Card> card) {
    Cards cards = getCardsOnTable();
    for (int i = 0; i < cards.size(); i++ ) {
        if (cards.at(i) == card) {
            return true;
        }
    }
    return false;
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
 * Set current player to index
 * Set start to the player who has 7S
 */
void Model::setCurrentPlayer(int currentPlayer) {
    currentPlayer_ = currentPlayer;
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
void Model::addPlayerCards(int playerNum, Cards &cards) {
    for (int i = 0; i < cards.size(); i++) {
        player(playerNum)->addCard(cards.at(i));
    }
    notify();
}

/**
 * Play a card
 */
void Model::playCard(int playerNum, Card card) {
    player(playerNum)->playCard(card);
    donePlay();
}

/**
 * Discard a card
 */
void Model::discardCard(int playerNum, Card card) {
    player(playerNum)->discardCard(card);
    donePlay();
}

/**
 * 1. Set next player
 * 2. Increment # plays
 * 3. Notify
 */
void Model::donePlay() {
    currentPlayer_ = (currentPlayer_ + 1) % NUM_PLAYERS;
    numPlays_++;
    notify();
}
