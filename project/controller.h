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

   void startRound();
   void endRound();
   void autoPlay();
   void rageQuit(int);
   void togglePlayer(int);
   bool playHumanCard(int, Card);
   bool discardHumanCard(int, Card);
   void playComputer(int);

   void shuffleCards(Cards &);

private:
   Model *model_;
   std::mt19937 rng;
}; // Controller

#endif
