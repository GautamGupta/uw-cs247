#include "computerplayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() : Player() {}

bool ComputerPlayer::isHuman() {
    return false;
}

void ComputerPlayer::playCard(Card* card) {

}

void ComputerPlayer::discardCard(Cards, std::shared_ptr<Card>){

}
