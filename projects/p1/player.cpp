#include "player.h"
#include <string>
#include <cassert>
using namespace std;

Player::Player() {}

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

void Player::addOriginalCard(shared_ptr<Card> card) {
    originalCards_.push_back(card);
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getScore();

    return out;
}
