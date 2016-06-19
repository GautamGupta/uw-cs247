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
    void addPlayer(std::shared_ptr<Player>);

private:
    std::vector< std::shared_ptr<Player> > players_;
}; // Model


#endif
