#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "player.h"
#include "card.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    virtual ~HumanPlayer();

    bool isHuman();
};

#endif
