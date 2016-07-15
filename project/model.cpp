/**
 * Model class. Responsible keeping track of the players and gameplay.
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

using namespace std;

/**
 * Initialize 4 humans
 * Set current player to -1 (means game isn't in progress)
 * Set num plays to 0 (num cards played / discarded)
 */
Model::Model() : currentPlayer_(-1), numTurns_(0) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players_.push_back(unique_ptr<Player>(new HumanPlayer()));
    }
}

/**
 * Get player whose turn it is to play
 *
 * -1 means game isn't in progress
 */
int Model::getCurrentPlayer() const {
    return currentPlayer_;
}

/**
 * Check if round just started
 */
bool Model::isRoundStarting() const {
    return (isGameInProgress() && numTurns_ == 0);
}

/**
 * Check if 52 cards have been played / discarded in the round
 * ie. if round is over
 */
bool Model::isRoundOver() const {
    return numTurns_ == NUM_CARDS;
}

/**
 * Simple state check to see if game is in progress
 */
bool Model::isGameInProgress() const {
    return getCurrentPlayer() != -1;
}

/**
 * Check if player has > 80 pts
 */
bool Model::isGameOver() const {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players_.at(i)->isGameOver()) {
            return true;
        }
    }
    return false;
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
 * Get legal plays for a player. We need to supply cards on table.
 * @param  playerNum Index position of player
 */
Cards Model::getPlayerLegalPlays(int playerNum) const {
    return players_.at(playerNum)->getLegalPlays(getCardsOnTable());
}

/**
 * Get player's current cards (that can be played / discarded)
 */
const Cards& Model::getPlayerCurrentCards(int playerNum) const {
    return players_.at(playerNum)->getCurrentCards();
}

/**
 * Get player's discarded cards
 */
const Cards& Model::getPlayerDiscardedCards(int playerNum) const {
    return players_.at(playerNum)->getDiscardedCards();
}

/**
 * Checks if player is a human
 */
bool Model::isPlayerHuman(int playerNum) const {
    return players_.at(playerNum)->isHuman();
}

/**
 * Get player's current round score
 */
int Model::getPlayerScore(int playerNum) const {
    return players_.at(playerNum)->getScore();
}

/**
 * Get player's previous round score
 */
 int Model::getPlayerPreviousScore(int playerNum) const {
     return players_.at(playerNum)->getPreviousScore();
 }

/**
 * Get player's total score (previous + current rounds)
 */
int Model::getPlayerTotalScore(int playerNum) const {
    return players_.at(playerNum)->getTotalScore();
}

/**
 * See what's the lowest score in the game
 */
int Model::getLowestPlayerScore() const {
    int getLowestPlayerScore = getPlayerTotalScore(0);
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (getPlayerTotalScore(i) < getLowestPlayerScore) {
            getLowestPlayerScore = getPlayerTotalScore(i);
        }
    }
    return getLowestPlayerScore;
}

/**
 * Set current player to index
 *
 * Start: To the player who has 7S
 */
void Model::setCurrentPlayer(int currentPlayer) {
    currentPlayer_ = currentPlayer;
    notify();
}

/**
 * Switch player type
 */
void Model::togglePlayer(int playerNum) {
    // Can't really refactor duplicate code due to use of unique_ptr
    if (isPlayerHuman(playerNum)) {
        unique_ptr<Player> newPlayer(new ComputerPlayer(*players_.at(playerNum)));
        players_[playerNum].release();
        players_.erase(players_.begin() + playerNum);
        players_.insert(players_.begin() + playerNum, move(newPlayer));
    } else {
        unique_ptr<Player> newPlayer(new HumanPlayer(*players_.at(playerNum)));
        players_[playerNum].release();
        players_.erase(players_.begin() + playerNum);
        players_.insert(players_.begin() + playerNum, move(newPlayer));
    }

    // Avoid double notify when game is in progress
    if (!isGameInProgress()) {
        notify();
    }
}

/**
 * Add cards to player
 * Doesn't notify to avoid double notify
 */
void Model::addPlayerCards(int playerNum, Cards &cards) {
    players_.at(playerNum)->addCards(cards);
}

/**
 * Play a card (and notify)
 */
void Model::playCard(int playerNum, Card card) {
    players_.at(playerNum)->playCard(card);
    doneTurn();
}

/**
 * Discard a card (and notify)
 */
void Model::discardCard(int playerNum, Card card) {
    players_.at(playerNum)->discardCard(card);
    doneTurn();
}

/**
 * 1. Increment # plays
 * 2. Set next player (and notify)
 */
void Model::doneTurn() {
    numTurns_++;
    setCurrentPlayer((getCurrentPlayer() + 1) % NUM_PLAYERS);
}

/**
 * Start round for every player
 */
void Model::startRound() {
    numTurns_ = 0;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        players_.at(i)->startRound();
    }
}

/**
 * Resets the game
 */
void Model::reset() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players_.at(i)->reset();
    }
    currentPlayer_ = -1;
    numTurns_ = 0;

    notify();
}
