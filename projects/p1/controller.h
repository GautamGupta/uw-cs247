#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

class Model;
class View;

class Controller {
public:
   Controller(Model*, View*);
   Model* model();
   View* view();
   void inputPlayers();

private:
   Model *model_;
   View *view_;
}; // Controller

#endif
