#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

#include "main.h"
#include "card.h"
#include <vector>
#include <random>

/** Documentation of methods in .cpp file */

class Model;

class Controller {
public:
    Controller(Model*);

    void startRound(Cards &);
    void playComputer(int);
    void playHuman(int, Card);
    void doneTurn();
    void rageQuit(int);
    void togglePlayer(int);

    void shuffleCards(Cards &);

    void startButtonClicked(int = DEFAULT_SEED);
    void endButtonClicked();

    class InvalidPlayException{};

private:
    Model *model_;
    std::mt19937 rng;
};

#endif
