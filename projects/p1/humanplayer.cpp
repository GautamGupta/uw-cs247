#include "humanplayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() : Player() {}

bool HumanPlayer::isHuman() {
    return true;
}

void HumanPlayer::playCard(Card* card) {

}

void HumanPlayer::discardCard(Cards cardsOnTable, std::shared_ptr<Card> discardedCard){
  if(getLegalPlays(cardsOnTable).size() > 0){
    cout << "You have a legal play. You may not discard." << endl;
  }
  else {
    getDiscardedCards().push_back(discardedCard);
    int index = 0;
    bool cardInHand = false;

    // Find index of discardedCard
    // Need to check if discardedCard is actually in current hand
    for(vector<shared_ptr<Card> >::iterator it = getCurrentCards().begin(); it != getCurrentCards().end(); ++it) {
      if((*it)->getSuit() == discardedCard->getSuit() && (*it)->getRank() == discardedCard->getRank()) {
        cardInHand = true;
        break;
      }
      index++;
    }

    if(cardInHand){
      getCurrentCards().erase(getCurrentCards().begin() + index); // Removes the card in hand
    }
    else {
      cout << "CANNOT DISCARD A CARD NOT IN YOUR HAND" << endl;
    }
  }

}
