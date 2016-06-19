#include "player.h"
#include <string>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

Player::Player() : score_(0), previousScore_(0) {}

void Player::startRound() {
    previousScore_ += score_;
    score_ = 0;
    originalCards_.clear();
    currentCards_.clear();
    playedCards_.clear();
    discardedCards_.clear();
}

void Player::endRound() {
    int score = 0;
    for (int i = 0; i < getDiscardedCards().size(); i++) {
      score += getDiscardedCards().at(i)->getRank();
    }
    score_ = score;
}

bool Player::checkEndGame() {
    if(calculateScore() >= 80){
      return true;
    }
    return false;
}

/* Get functions */

vector< shared_ptr<Card> > Player::getOriginalCards() const {
    return originalCards_;
}

vector< shared_ptr<Card> > Player::getCurrentCards() const {
    return currentCards_;
}

vector< shared_ptr<Card> > Player::getPlayedCards() const {
    return playedCards_;
}

vector< shared_ptr<Card> > Player::getDiscardedCards() const {
    return discardedCards_;
}

int Player::getPreviousScore() const {
    return previousScore_;
}
int Player::getScore() const {
    return score_;
}

int Player::calculateScore() const {
    return previousScore_ + score_;
}

// Get legal plays
vector< shared_ptr<Card> > Player::getLegalPlays(Cards cardsOnTable) {
    Cards legalPlays;

    // Outer loop: current cards in hand
    for (int i = 0; i < getCurrentCards().size(); i++) {
        bool isLegalPlay = false;

        // If card in hand has same suit and is +/- 1 rank of a played card, then it is legal. It is also legal if card is a 7
        if (getCurrentCards().at(i)->getRank() == SEVEN) {
            isLegalPlay = true;
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

// Checks if a card is in the player's hand. If found it will return the index, if not it will return -1
int Player::cardInHand(Card card) {
    int index = 0;
    bool cardInHand = false;

    for(vector<shared_ptr<Card> >::iterator it = getCurrentCards().begin(); it != getCurrentCards().end(); ++it) {
        if (**it == card) {
            cardInHand = true;
            break;
        }
        index++;
    }
    if(!cardInHand){
      index = -1;
    }
    return index;
}

void Player::playCard(Card card) {
    int index = cardInHand(card);
    if(index >= 0){
        playedCards_.push_back(getCurrentCards().at(index));
        currentCards_.erase(getCurrentCards().begin() + index);
    } else {
        throw CardNotFoundException();
    }
}

void Player::discardCard(Card card) {
    int index = cardInHand(card);
    if (index >= 0) {
        discardedCards_.push_back(getCurrentCards().at(index));
        currentCards_.erase(getCurrentCards().begin() + index); // Removes the card in hand
    } else {
        throw CardNotFoundException();
    }
}

void Player::addCard(shared_ptr<Card> card) {
    originalCards_.push_back(card);
    currentCards_.push_back(card);
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getScore();

    return out;
}
