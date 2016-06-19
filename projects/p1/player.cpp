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

int Player::getScore() const {
    return score_;
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

// // Discard card, need to convert a string into a card
// void Player::discardCard(){
//
//   // for computer player
//   // If a computer player has legal plays, he is not able to discard
//   if(getLegalPlays().size() > 0){
//     cout << "You have a legal play. You may not discard." << endl;
//   }
//   // If a computer player has no legal plays, he must discard his first card.
//   else{
//     discardedCards_.push_back(getCurrentCards().at(0));
//     currentCards_.erase(0);
//   }
// }
//
// FOR HUMAN: Discard card, need to convert a string into a card
// void Player::discardCard(Cards cardsOnTable, shared_ptr <Card> discardedCard){
//   if(getLegalPlays(cardsOnTable).size() > 0){
//     cout << "You have a legal play. You may not discard." << endl;
//   }
//   else {
//     discardedCards_.push_back(discardedCard);
//     int index = 0;
//     bool cardInHand = false;
//
//     // Find index of discardedCard
//     // Need to check if discardedCard is actually in current hand
//     for(vector<shared_ptr<Card> >::iterator it = getCurrentCards().begin(); it != currentCards_.end(); ++it) {
//       if((*it)->getSuit() == discardedCard->getSuit() && (*it)->getRank() == discardedCard->getRank()) {
//         cardInHand = true;
//         break;
//       }
//       index++;
//     }
//
//     if(cardInHand){
//       currentCards_.erase(currentCards_.begin() + index); // Removes the card in hand
//     }
//     else {
//       cout << "CANNOT DISCARD A CARD NOT IN YOUR HAND" << endl;
//     }
//   }
// }




void Player::addOriginalCard(shared_ptr<Card> card) {
    originalCards_.push_back(card);
    currentCards_.push_back(card);
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getScore();

    return out;
}
