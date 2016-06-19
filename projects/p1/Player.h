#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include <ostream>
#include <vector>

enum PlayerType { HUMAN, COMPUTER };

class Player {
public:
    Player();

    std::vector< std::shared_ptr<Card> > getOriginalCards() const;
    std::vector< std::shared_ptr<Card> > getCurrentCards() const;
    std::vector< std::shared_ptr<Card> > getDiscardedCards() const;
    int getScore() const;

    std::vector< std::shared_ptr<Card> > getLegalPlays();
    virtual void playCard(Card*) = 0;
    virtual void discardCard(Card*) = 0;

private:
    std::vector< std::shared_ptr<Card> > originalCards_;
    std::vector< std::shared_ptr<Card> > currentCards_;
    std::vector< std::shared_ptr<Card> > discardedCards_;
    int score_;
};

std::ostream &operator<<(std::ostream &, const Player &);

#endif
