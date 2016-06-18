#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

class Model;
class View;

class Controller {
public:
   Controller(Model*, View*);
   void start();

private:
   Model *model_;
   View *view_;
}; // Controller


#endif

