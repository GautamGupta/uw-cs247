#include "player.h"
#include <string>
#include <cassert>
using namespace std;

Player::Player(Type t) {
    type_ = t;
}

Type Player::getType() const {
    return type_;
}

int Card::getScore() const {
    return score_;
}

ostream &operator<<(ostream &out, const Player &p) {
    out << p.getType() << p.getScore();

    return out;
}

istream &operator>>(istream &in, Player &p) {
    string types = "hc";

    string str;
    in >> str;
    assert ( !in.fail() );

    // Read in the type, make sure it's valid
    p.type_ = (Type) types.find( str.at(0) );
    assert ( p.type_ != string::npos );

    return in;
}
