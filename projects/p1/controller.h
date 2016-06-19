#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

#include "Card.h"
#include <vector>

class Model;
class View;

class Controller {
public:
   Controller(Model*, View*);
   Model* model();
   View* view();

   void inputPlayers();
   void assignCards();
   void startRound();
   void endRound();
   void playHuman(int);

   void shuffleCards(Cards &);

private:
   Model *model_;
   View *view_;
}; // Controller

#endif
