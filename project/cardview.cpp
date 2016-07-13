#include "cardview.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include <gtkmm.h>

using namespace std;

CardView::CardView(Model* model, Controller* controller, View* view) : model_(model), controller_(controller), view_(view) {
    cardImage_ = new Gtk::Image(view_->getNullCardImage());
    set_image(*cardImage_);

    signal_clicked().connect(sigc::mem_fun(*this, &CardView::cardButtonClicked));
}

CardView::~CardView() {
	delete cardImage_;
}

void CardView::cardButtonClicked() {
    view_->displayMessage("Gautam", "Bo Peng says hi");
}

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
