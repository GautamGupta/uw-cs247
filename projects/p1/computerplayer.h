#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "player.h"
#include "Card.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer();

    bool isHuman();
    void playCard(Card);
};

#endif
