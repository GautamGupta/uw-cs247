#include "humanplayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() : Player() {}

bool HumanPlayer::isHuman() {
    return true;
}
