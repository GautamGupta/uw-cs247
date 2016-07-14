#include "humanplayer.h"

using namespace std;

HumanPlayer::HumanPlayer() : Player() {}

/**
 * Copy constructor for toggle
 */
HumanPlayer::HumanPlayer(const Player &player) : Player() {
    previousScore_  = player.getPreviousScore();
    score_          = player.getScore();
    originalCards_  = player.getOriginalCards();
    currentCards_   = player.getCurrentCards();
    playedCards_    = player.getPlayedCards();
    discardedCards_ = player.getDiscardedCards();
}

HumanPlayer::~HumanPlayer() {}

/**
 * Return true as this is the human class
 */
bool HumanPlayer::isHuman() {
    return true;
}
