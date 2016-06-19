#include "player.h"
#include <string>
#include <cassert>
using namespace std;

Player::Player() {}

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





void Player::addOriginalCard(shared_ptr<Card> card) {
    originalCards_.push_back(card);
    currentCards_.push_back(card);
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getScore();

    return out;
}
