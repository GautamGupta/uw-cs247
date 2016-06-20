#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "player.h"
#include "card.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();

    bool isHuman();
};

#endif
