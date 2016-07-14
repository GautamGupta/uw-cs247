#include "main.h"
#include "player.h"
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

Player::Player() : score_(0), previousScore_(0) {}

Player::~Player() {}

/**
 * Get score of current round
 */
int Player::getScore() const {
    return score_;
}

/**
 * Get score from previous rounds (cumulative)
 */
int Player::getPreviousScore() const {
    return previousScore_;
}

/**
 * Calculate total score
 */
int Player::getTotalScore() const {
    return getPreviousScore() + getScore();
}

/**
 * See if the user has > 80 pts
 */
bool Player::isGameOver() const {
    return (getTotalScore() >= NUM_POINTS);
}

/**
 * Original card maintains the cards assigned to the player
 * at the start of the round.
 */
const Cards& Player::getOriginalCards() const {
    return originalCards_;
}

/**
 * Cards in player's hand
 */
const Cards& Player::getCurrentCards() const {
    return currentCards_;
}

/**
 * Cards the player has played
 */
const Cards& Player::getPlayedCards() const {
    return playedCards_;
}

/**
 * Cards the player has discarded
 */
const Cards& Player::getDiscardedCards() const {
    return discardedCards_;
}

/**
 * Get legal plays per straight game play. Needs played cards for the round.
 */
Cards Player::getLegalPlays(Cards cardsOnTable) const {
    Cards legalPlays;
    Card firstCard = Card(SPADE, SEVEN);

    // Outer loop: current cards in hand
    for (int i = 0; i < getCurrentCards().size(); i++) {
        bool isLegalPlay = false;

        // Only legal card is 7S if there is a 7S on your hand
        if (*getCurrentCards().at(i) == firstCard) {
            legalPlays.clear();
            legalPlays.push_back(getCurrentCards().at(i));
            return legalPlays;

        // Legal if card is a 7
        } else if (getCurrentCards().at(i)->getRank() == SEVEN) {
            isLegalPlay = true;

        // If card in hand has same suit and is +/- 1 rank of a played card, then it is legal
        } else {
            for (int j = 0; j < cardsOnTable.size(); j++) {
                if (cardsOnTable.at(j)->getSuit() == getCurrentCards().at(i)->getSuit()
                    && abs((int) cardsOnTable.at(j)->getRank() - (int) getCurrentCards().at(i)->getRank()) <= 1) {
                    isLegalPlay = true;
                }
            }
        }

        if (isLegalPlay) {
            legalPlays.push_back(getCurrentCards().at(i));
        }
    }

    return legalPlays;
}

/**
 * Checks if a card is in the player's hand.
 * If found it will return the index.
 * If not it will return -1
 */
int Player::getPositionInCurrentCards(Card card) const {
    for (int i = 0; i < getCurrentCards().size(); i++) {
        if (*getCurrentCards().at(i) == card) {
            return i;
        }
    }

    return -1;
}

/**
 * Assign cards to player (add to original and current)
 */
void Player::addCards(Cards &cards) {
    originalCards_.insert(originalCards_.end(), cards.begin(), cards.end());
    currentCards_.insert(currentCards_.end(), cards.begin(), cards.end());
}

/**
 * Add score to previous score, clear all arrays, set score to 0
 */
void Player::startRound() {
    int scoreTemp = getTotalScore();
    reset();
    previousScore_ = scoreTemp;
}

/**
 * Remove card from current cards and add to played cards
 */
void Player::playCard(Card card) {
    int index = getPositionInCurrentCards(card);
    if (index >= 0) {
        playedCards_.push_back(getCurrentCards().at(index));
        currentCards_.erase(getCurrentCards().begin() + index);
    } else {
        throw CardNotFoundException();
    }
}

/**
 * Remove card from current cards and add to discarded cards
 * Add rank to score
 */
void Player::discardCard(Card card) {
    int index = getPositionInCurrentCards(card);
    if (index >= 0) {
        discardedCards_.push_back(getCurrentCards().at(index));
        currentCards_.erase(getCurrentCards().begin() + index); // Removes the card in hand
        score_ += card.getRank() + 1; // index + 1
    } else {
        throw CardNotFoundException();
    }
}

/**
 * Reset a player
 */
void Player::reset() {
    previousScore_ = 0;
    score_ = 0;
    originalCards_.clear();
    currentCards_.clear();
    playedCards_.clear();
    discardedCards_.clear();
}
