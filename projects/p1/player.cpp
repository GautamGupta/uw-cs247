#include "player.h"
#include <string>
#include <cassert>
using namespace std;

Player::Player() {}

int Player::getScore() const {
    return score_;
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getScore();

    return out;
}
