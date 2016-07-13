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

    move(player.getOriginalCards().begin(), player.getOriginalCards().end(), back_inserter(originalCards_));
    move(player.getCurrentCards().begin(), player.getCurrentCards().end(), back_inserter(currentCards_));
    move(player.getPlayedCards().begin(), player.getPlayedCards().end(), back_inserter(playedCards_));
    move(player.getDiscardedCards().begin(), player.getDiscardedCards().end(), back_inserter(discardedCards_));
}

/**
 * Return false as this is the computer class
 */
bool ComputerPlayer::isHuman() {
    return false;
}
