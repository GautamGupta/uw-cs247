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

    void addCard(std::shared_ptr<Card>);
    void startRound();
    void endRound();
    bool checkEndGame();

    int cardInHand(Card card);
    void playCard(Card);
    void discardCard(Card);

    class CardNotFoundException{};

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
