/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

#include "main.h"
#include "model.h"
#include "card.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;

Model::Model() : currentPlayer_(-1), numPlays_(0) {
    // Initialize 4 humans
    for (int i = 0; i < NUM_PLAYERS; i++) {
        unique_ptr<Player> humanPlayer(new HumanPlayer());
        players_.push_back(move(humanPlayer));
    }
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
    return players_.at(i)->isHuman();
}

/**
 * Start round for every player
 */
void Model::startRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players_.at(i)->startRound();
    }
    notify();
}

/**
 * Resets the game
 */
void Model::reset() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players_.at(i)->reset();
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
        if (players_.at(i)->checkEndGame()) {
            return true;
        }
    }
    return false;
}

/**
 * See what's the lowest score in the game
 */
int Model::lowestScore() {
    int lowestScore = getPlayerTotalScore(0);
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (getPlayerTotalScore(i) < lowestScore) {
            lowestScore = getPlayerTotalScore(i);
        }
    }
    return lowestScore;
}

/**
 * Calculates score of player at index i
 */
int Model::getPlayerTotalScore(int i) const {
    return players_.at(i)->getTotalScore();
}

/**
 * Add all cards assigned to players to an array and return (in order)
 */
Cards Model::getDeck() const {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        cards.insert(cards.end(), players_.at(i)->getOriginalCards().begin(), players_.at(i)->getOriginalCards().end());
    }

    return cards;
}

/**
 * Get all the played cards for the round
 */
Cards Model::getCardsOnTable() const {
    Cards cards;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        cards.insert(cards.end(), players_.at(i)->getPlayedCards().begin(), players_.at(i)->getPlayedCards().end());
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
        for (int j = 0; j < players_.at(i)->getPlayedCards().size(); j++) {
            shared_ptr<Card> card = players_.at(i)->getPlayedCards().at(j);
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
    return players_.at(playerNum)->getLegalPlays(getCardsOnTable());
}

/**
 * Switch player type
 * @param int Index to toggle
 */
void Model::togglePlayer(int playerNum) {
    if (isHuman(playerNum)) {
        unique_ptr<Player> newPlayer(new ComputerPlayer(*players_.at(playerNum)));
        players_[playerNum].release();
        players_.insert(players_.begin() + playerNum, move(newPlayer));
    } else {
        unique_ptr<Player> newPlayer(new HumanPlayer(*players_.at(playerNum)));
        players_[playerNum].release();
        players_.insert(players_.begin() + playerNum, move(newPlayer));
    }
}

/**
 * Add card to player
 */
void Model::addPlayerCards(int playerNum, Cards &cards) {
    for (int i = 0; i < cards.size(); i++) {
        players_.at(playerNum)->addCard(cards.at(i));
    }
    notify();
}

/**
 * Play a card
 */
void Model::playCard(int playerNum, Card card) {
    players_.at(playerNum)->playCard(card);
    donePlay();
}

/**
 * Discard a card
 */
void Model::discardCard(int playerNum, Card card) {
    players_.at(playerNum)->discardCard(card);
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
    return players_.at(playerNum)->getScore();
}
