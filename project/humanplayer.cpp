#include "humanplayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() : Player() {}

/**
 * Copy constructor for toggle
 */
HumanPlayer::HumanPlayer(const Player &player) : Player() {
    previousScore_  = player.getPreviousScore();
    score_          = player.getScore();

    move(player.getOriginalCards().begin(), player.getOriginalCards().end(), back_inserter(originalCards_));
    move(player.getCurrentCards().begin(), player.getCurrentCards().end(), back_inserter(currentCards_));
    move(player.getPlayedCards().begin(), player.getPlayedCards().end(), back_inserter(playedCards_));
    move(player.getDiscardedCards().begin(), player.getDiscardedCards().end(), back_inserter(discardedCards_));
}

HumanPlayer::~HumanPlayer() {}

/**
 * Return true as this is the human class
 */
bool HumanPlayer::isHuman() {
    return true;
}
