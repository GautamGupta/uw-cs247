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
    int startPlayer();
    std::shared_ptr<Player> player(int);
    Cards getDeck();
    Cards getCardsOnTable();
    bool cardWasPlayed(std::shared_ptr<Card>);
    SuitCards getSuitCardsOnTable();
    Cards getLegalPlays(int);

    void setStartPlayer(int);
    void replacePlayer(int, std::shared_ptr<Player>);
    void addPlayerCards(int, Cards &);
    void startRound();
    void endRound();
    bool isGameOver();
    int lowestScore();

private:
    Players players_;
    int startPlayer_; // Index of player that starts the round (has 7S)
}; // Model

#endif
