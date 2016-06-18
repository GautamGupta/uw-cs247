#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

class Model;

class Controller {
public:
   Controller(Model*, View*);

private:
   Model *model_;
   View *view_;
}; // Controller


#endif

