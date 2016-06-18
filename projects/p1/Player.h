#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>

class Player {
public:
    Player();
    int getScore() const;

private:
    int score_;
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif
