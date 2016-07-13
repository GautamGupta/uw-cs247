/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

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
    Players players();
    std::shared_ptr<Player> player(int);
    int currentPlayer() const;
    Cards getDeck() const;
    Cards getCardsOnTable() const;
    SuitCards getSuitCardsOnTable();
    Cards getLegalPlays(int);

    void setCurrentPlayer(int);
    void replacePlayer(int, std::shared_ptr<Player>);
    void addPlayerCards(int, Cards &);
    void playCard(int, Card);
    void discardCard(int, Card);
    void startRound();
    void donePlay();
    bool isRoundOver();
    void endRound();
    bool isGameOver();
    int lowestScore();
    void reset();

    const Cards& getPlayerCurrentCards(int);

private:
    Players players_;
    int currentPlayer_;   // Index of player that has the next turn
    int numPlays_;        // Number of plays that have happened in the round (# plays + # discards)
}; // Model

#endif
