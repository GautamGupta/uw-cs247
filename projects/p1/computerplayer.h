#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "player.h"
#include "card.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer();
    ComputerPlayer(const Player&);

    bool isHuman();
};

#endif
