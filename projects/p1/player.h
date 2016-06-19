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
    int calculateScore() const;

    Cards getLegalPlays(Cards);
    virtual bool isHuman() = 0;
    virtual void playCard(Card*) = 0;
    virtual void discardCard(Cards, std::shared_ptr<Card>) = 0;

    void addOriginalCard(std::shared_ptr<Card>);
    void startRound();
    void endRound();
    bool checkEndGame();


private:
    Cards originalCards_;
    Cards currentCards_;
    Cards playedCards_;
    Cards discardedCards_;
    int score_;
    int previousScore_;
};

std::ostream &operator<<(std::ostream &, const Player &);

typedef std::vector< std::shared_ptr<Player> > Players;

#endif
