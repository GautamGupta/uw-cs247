#include "cardview.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include <gtkmm.h>

using namespace std;

CardView::CardView(Model* model, Controller* controller, View* view) : model_(model), controller_(controller), view_(view) {
    cardImage_ = new Gtk::Image(view_->getNullCardImage());
    set_image(*cardImage_);
    set_sensitive(false);

    signal_clicked().connect(sigc::mem_fun(*this, &CardView::cardButtonClicked));
}

CardView::~CardView() {
    delete cardImage_;
}

void CardView::cardButtonClicked() {
    try {
        controller_->cardButtonClicked(*card_);
    } catch (Player::CardNotFoundException &e) {
        view_->displayMessage(View::TXT_ERROR, "The card was not found.");
    } catch (Controller::InvalidPlayException &e) {
        view_->displayMessage(View::TXT_ERROR, "The card is not legal play for this turn.");
    }
}

/**
 * Set the view to a particular card
 * @param card        Must be a ptr so that NULL can be passed in
 * @param sensitivity Enabled?
 */
void CardView::setCard(shared_ptr<Card> card, bool sensitivity /* = true */) {
    card_ = card;
    set_sensitive(sensitivity);
    delete cardImage_;

    if (card == NULL) {
        cardImage_ = new Gtk::Image(view_->getNullCardImage());
    } else {
        cardImage_ = new Gtk::Image(view_->getCardImage(*card));
    }

    set_image(*cardImage_);
}
