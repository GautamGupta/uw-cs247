#include "computerplayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player() {}

ComputerPlayer::ComputerPlayer(const Player &player) : Player() {
    previousScore_  = player.getPreviousScore();
    score_          = player.getScore();
    originalCards_  = player.getOriginalCards();
    currentCards_   = player.getCurrentCards();
    playedCards_    = player.getPlayedCards();
    discardedCards_ = player.getDiscardedCards();
}

bool ComputerPlayer::isHuman() {
    return false;
}
