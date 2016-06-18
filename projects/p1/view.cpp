/**
 * View class. Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 */

#include "view.h"
#include "model.h"
#include <iostream>

using namespace std;

View::View(Model *m) : model_(m) {}

View::~View() {}
