#include "humanplayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() : Player() {}

HumanPlayer::~HumanPlayer() {}

/**
 * Return true as this is the human class
 */
bool HumanPlayer::isHuman() {
    return true;
}
