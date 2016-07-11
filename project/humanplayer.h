#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "player.h"
#include "card.h"

/** Documentation of methods in .cpp file */

class HumanPlayer : public Player {
public:
    HumanPlayer();
    HumanPlayer(const Player&);
    virtual ~HumanPlayer();

    bool isHuman();
};

#endif
