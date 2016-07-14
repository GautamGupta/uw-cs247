#ifndef _PLAYER_
#define _PLAYER_

#include "card.h"
#include <memory>
#include <vector>

/** Documentation of methods in .cpp file */

class Player {
public:
    Player();
    virtual ~Player();
    virtual bool isHuman() const = 0;

    int getScore() const;
    int getPreviousScore() const;
    int getTotalScore() const;
    bool isGameOver() const;
    const Cards& getOriginalCards() const;
    const Cards& getCurrentCards() const;
    const Cards& getPlayedCards() const;
    const Cards& getDiscardedCards() const;
    Cards getLegalPlays(Cards) const;
    int getPositionInCurrentCards(Card) const;

    void addCards(Cards &);
    void startRound();
    void playCard(Card);
    void discardCard(Card);
    void reset();

    class CardNotFoundException{};

protected:
    int score_;
    int previousScore_;
    Cards originalCards_;
    Cards currentCards_;
    Cards playedCards_;
    Cards discardedCards_;
};

typedef std::vector< std::unique_ptr<Player> > Players;

#endif
