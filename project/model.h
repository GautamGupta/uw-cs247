#ifndef ST_MODEL_H
#define ST_MODEL_H

/** Documentation of methods in .cpp file */

#include "card.h"
#include "player.h"
#include "subject.h"
#include <memory>
#include <vector>

class Model : public Subject {
public:
    Model();

    int getCurrentPlayer() const;
    bool isRoundOver() const;
    bool isGameInProgress() const;
    bool isGameOver() const;
    Cards getDeck() const;
    Cards getCardsOnTable() const;
    Cards getPlayerLegalPlays(int) const;
    const Cards& getPlayerCurrentCards(int) const;
    const Cards& getPlayerDiscardedCards(int) const;
    bool isPlayerHuman(int) const;
    int getPlayerScore(int) const;
    int getPlayerTotalScore(int) const;
    int getLowestPlayerScore() const;

    void setCurrentPlayer(int);
    void togglePlayer(int);
    void addPlayerCards(int, Cards &);
    void playCard(int, Card);
    void discardCard(int, Card);
    void doneTurn();
    void startRound();
    void reset();

private:
    Players players_;
    int currentPlayer_;
    int numTurns_;
};

#endif
