/**
 * Model class. Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 */

#ifndef ST_MODEL_H
#define ST_MODEL_H

#include "card.h"
#include "player.h"
#include <vector>

class Model {
public:
    Model();
    std::shared_ptr<Player> player(int);
    Cards getCardsOnTable();
    SuitCards getSuitCardsOnTable();
    int startPlayer();

    void setStartPlayer(int);
    void addPlayer(std::shared_ptr<Player>);
    void addPlayerCard(int, std::shared_ptr<Card>);
    void debug();

private:
    Players players_;
    int startPlayer_; // Index of player that starts the round (has 7S)
}; // Model

#endif
