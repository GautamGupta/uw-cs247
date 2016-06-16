#ifndef ST_CONTROLLER_H
#define ST_CONTROLLER_H

class Model;

class Controller {
public:
   Controller(Model*);

private:
   Model *model_;
}; // Controller


#endif

