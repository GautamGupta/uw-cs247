#include "humanplayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() : Player() {}

HumanPlayer::~HumanPlayer() {}

bool HumanPlayer::isHuman() {
    return true;
}
