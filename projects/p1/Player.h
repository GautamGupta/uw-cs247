#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include <ostream>
#include <vector>

enum PlayerType { HUMAN, COMPUTER };

class Player {
public:
    Player();

    Cards getOriginalCards() const;
    Cards getCurrentCards() const;
    Cards getPlayedCards() const;
    Cards getDiscardedCards() const;
    int getScore() const;
    int getPreviousScore() const;

    Cards getLegalPlays();
    virtual bool isHuman() = 0;
    virtual void playCard(Card*) = 0;
    virtual void discardCard(Card*) = 0;

    void addOriginalCard(std::shared_ptr<Card>);

private:
    Cards originalCards_;
    Cards currentCards_;
    Cards playedCards_;
    Cards discardedCards_;
    int score_;
    int previousScore_;
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif
