#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "player.h"
#include "Card.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();

    bool isHuman();
    void playCard(Card);
};

#endif
