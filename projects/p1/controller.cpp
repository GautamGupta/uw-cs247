/**
 * Controller class. Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 */

#include "controller.h"
#include "model.h"
#include "view.h"

Controller::Controller(Model *m, View *v) : model_(m), view_(v) {}

void Controller::start() {
}
