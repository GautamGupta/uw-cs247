#ifndef _PLAYER_
#define _PLAYER_

#include "card.h"
#include <ostream>
#include <memory>
#include <vector>

/** Documentation of methods in .cpp file */

enum PlayerType { HUMAN, COMPUTER };

class Player {
public:
    Player();
    virtual ~Player();

    const Cards& getOriginalCards() const;
    const Cards& getCurrentCards() const;
    const Cards& getPlayedCards() const;
    const Cards& getDiscardedCards() const;
    int getScore() const;
    int getPreviousScore() const;
    int getTotalScore() const;

    Cards getLegalPlays(Cards);
    virtual bool isHuman() = 0;

    void addCard(std::shared_ptr<Card>);
    void startRound();
    bool checkEndGame() const;
    void reset();

    int cardInHand(Card);
    void playCard(Card);
    void discardCard(Card);

    class CardNotFoundException{};

protected:
    Cards originalCards_;
    Cards currentCards_;
    Cards playedCards_;
    Cards discardedCards_;
    int score_;
    int previousScore_;
};

std::ostream &operator<<(std::ostream &, const Player &);

typedef std::vector< std::unique_ptr<Player> > Players;

#endif
