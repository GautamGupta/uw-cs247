#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>
#include <istream>

enum Type { HUMAN, COMPUTER };

class Player {
    friend std::istream &operator>>(std::istream &, Card &);

public:
    Player(Type);
    Type getType() const;
    int getScore() const;

private:
    Type type_;
    int score_;
};

std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
