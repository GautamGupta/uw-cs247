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

   void startButtonClicked(int = DEFAULT_SEED);
   void endButtonClicked();

   void startRound(Cards &);
   void endRound();
   void autoPlay();
   void rageQuit(int);
   void togglePlayer(int);
   void playHuman(int, Card);
   void playComputer(int);

   void shuffleCards(Cards &);

   class InvalidPlayException{};

private:
   Model *model_;
   std::mt19937 rng;
};

#endif
