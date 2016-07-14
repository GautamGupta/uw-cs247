#include "computerplayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player() {}

ComputerPlayer::~ComputerPlayer() {}

/**
 * Copy constructor for toggle
 */
ComputerPlayer::ComputerPlayer(const Player &player) : Player() {
    previousScore_  = player.getPreviousScore();
    score_          = player.getScore();
    originalCards_  = player.getOriginalCards();
    currentCards_   = player.getCurrentCards();
    playedCards_    = player.getPlayedCards();
    discardedCards_ = player.getDiscardedCards();
}

/**
 * Return false as this is the computer class
 */
bool ComputerPlayer::isHuman() const {
    return false;
}
