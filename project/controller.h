#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

#include "card.h"
#include <vector>
#include <random>

/** Documentation of methods in .cpp file */

class Model;

class Controller {
public:
   Controller(Model*);
   Model* model();

   void startButtonClicked(int = 0);
   void endButtonClicked();

   void inputPlayers();
   void assignCards();
   void startRound();
   void endRound();
   void playHuman(int);
   void playComputer(int);

   void shuffleCards(Cards &);

private:
   Model *model_;
   std::mt19937 rng;
}; // Controller

#endif