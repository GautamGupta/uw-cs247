#include "player.h"
#include <string>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

Player::Player() {}

/* Get functions */
vector< shared_ptr<Card> > Player::getOriginalCards() const {
    return originalCards_;
}

vector< shared_ptr<Card> > Player::getCurrentCards() const {
    return currentCards_;
}

vector< shared_ptr<Card> > Player::getDiscardedCards() const {
    return discardedCards_;
}

int Player::getScore() const {
    return score_;
}

// // Get legal plays
// vector< shared_ptr<Card> > Player::getLegalPlays() {
//   //loop through player's current cards
//   bool addLegalPlay = true;
//   vector< shared_ptr<Card> > legalPlays;
//   // Outer loop: current cards in hand
//   for (int i = 0; i < Player::getCurrentCards().size(); i++){
//     addLegalPlay = true;
//     for (int j = 0; j < totalPlayedCards_.size(); j++){
//       // If card in hand has same suit and is +/- 1 rank of a played card, then it is legal. It is also legal if card is a 7
//       if((*totalPlayedCards_.at(j).getSuit() == (*getCurrentCards().at(i)).getSuit() && ( *totalPlayedCards_.at(j).getRank() == (*getCurrentCards().at(i)).getRank() + 1 ||
//       *totalPlayedCards_.at(j).getRank() == (*getCurrentCards().at(i)).getRank() - 1)) || (*getCurrentCards().at(i)).getRank() == 7){
//         if(addLegalPlay){
//           legalPlays.push_back(getCurrentCards().at(i));
//           addLegalPlay = false;
//         }
//       }
//     }
//   }
//   return legalPlays;
// }
//
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
// // FOR HUMAN: Discard card, need to convert a string into a card
// void Player::discardCard(shared_ptr <Card> discardedCard){
//   if(getLegalPlays().size() > 0){
//     cout << "You have a legal play. You may not discard." << endl;
//   }
//   else{
//     discardedCards_.push_back(discardedCard);
//     int index = 0;
//     for(vector<shared_ptr<Card> >::iterator it = getCurrentCards().begin(); it != currentCards_.end(); ++it) {
//       if((*it)->getSuit() == discardedCard->getSuit() && (*it)->getRank() == discardedCard->getRank()) {
//         break;
//       }
//       index++;
//     }
//     currentCards_.erase(index);
//   }
// }




void Player::addOriginalCard(shared_ptr<Card> card) {
    originalCards_.push_back(card);
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getScore();

    return out;
}
