/**
 * View class. Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 */

#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include <iostream>

using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size,
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c)) {
	card.set( deck.null() );

	// Register view as observer of model
	model_->subscribe(this);

}

View::~View() {}

void View::update() {
  Suits suit = model_->suit();
  Faces face = model_->face();
  if ( suit == NOSUIT )
    card.set( deck.null() );
  else
    card.set( deck.image(face, suit) );

}

void View::nextButtonClicked() {
  controller_->nextButtonClicked();
}

void View::resetButtonClicked() {
  controller_->resetButtonClicked();
}
