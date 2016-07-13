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
#include <iostream>

using namespace std;

Model::Model() : currentPlayer_(-1), numPlays_(0) {
    // Initialize 4 humans
    for (int i = 0; i < NUM_PLAYERS; i++) {
        shared_ptr<Player> humanPlayer(new HumanPlayer());
        players_.push_back(humanPlayer);
    }
}

/**
 * Returns the player at index i
 */
shared_ptr<Player> Model::getPlayer(int i) const {
    return players_.at(i);
}

int Model::currentPlayer() const {
    return currentPlayer_;
}

/**
 * Set current player to index
 * Set start to the player who has 7S
 */
void Model::setCurrentPlayer(int currentPlayer) {
    currentPlayer_ = currentPlayer;
    notify();
}

/**
 * Checks if player at index i is human
 */
bool Model::isHuman(int i) {
    return getPlayer(i)->isHuman();
}

/**
 * Start round for every player
 */
void Model::startRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        getPlayer(i)->startRound();
    }
    notify();
}

/**
 * Calculate scores for every player
 */
void Model::endRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        getPlayer(i)->endRound();
    }
}

/**
 * Resets the game
 */
void Model::reset() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        getPlayer(i)->reset();
    }
    currentPlayer_ = -1;
    numPlays_ = 0;

    notify();
}

/**
 * Check if 52 cards have been played / discarded in the round
 * ie. if round is over
 */
bool Model::isRoundOver() {
    return numPlays_ == NUM_CARDS;
}

/**
 * Simple state check to see if game is in progress
 */
bool Model::isGameInProgress() {
    return currentPlayer() != -1;
}

/**
 * Check if player has > 80 pts
 */
bool Model::isGameOver() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (getPlayer(i)->checkEndGame()) {
            return true;
        }
    }
    return false;
}

/**
 * See what's the lowest score in the game
 */
int Model::lowestScore() {
    int lowestScore = getPlayer(0)->calculateScore();
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (getPlayer(i)->calculateScore() < lowestScore) {
            lowestScore = getPlayer(i)->calculateScore();
        }
    }
    return lowestScore;
}

/**
 * Calculates score of player at index i
 */
int Model::calculatePlayerScore(int i) const {
    return getPlayer(i)->calculateScore();
}

/**
 * Add all cards assigned to players to an array and return (in order)
 */
Cards Model::getDeck() const {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        cards.insert(cards.end(), getPlayer(i)->getOriginalCards().begin(), getPlayer(i)->getOriginalCards().end());
    }

    return cards;
}

/**
 * Get all the played cards for the round
 */
Cards Model::getCardsOnTable() const {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        cards.insert(cards.end(), getPlayer(i)->getPlayedCards().begin(), getPlayer(i)->getPlayedCards().end());
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
        suitCards[suit] = Cards();
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < getPlayer(i)->getPlayedCards().size(); j++) {
            shared_ptr<Card> card = getPlayer(i)->getPlayedCards().at(j);
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
    return getPlayer(playerNum)->getLegalPlays(getCardsOnTable());
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
        getPlayer(playerNum)->addCard(cards.at(i));
    }
    notify();
}

/**
 * Play a card
 */
void Model::playCard(int playerNum, Card card) {
    getPlayer(playerNum)->playCard(card);
    donePlay();
}

/**
 * Discard a card
 */
void Model::discardCard(int playerNum, Card card) {
    getPlayer(playerNum)->discardCard(card);
    donePlay();
}

/**
 * 1. Set next player
 * 2. Increment # plays
 * 3. Notify
 */
void Model::donePlay() {
    numPlays_++;
    setCurrentPlayer((currentPlayer() + 1) % NUM_PLAYERS);
}

const Cards& Model::getPlayerCurrentCards(int playerNum) {
    return players_.at(playerNum)->getCurrentCards();
}

const Cards& Model::getPlayerDiscardedCards(int playerNum) {
    return players_.at(playerNum)->getDiscardedCards();
}

int Model::getPlayerScore(int playerNum) const {
    return getPlayer(playerNum)->getScore();
}
