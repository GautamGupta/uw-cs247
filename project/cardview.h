#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include <gtkmm.h>

class Model;
class Controller;
class View;
class Card;

class CardView : public Gtk::Button {
public:
    CardView(Model*, Controller*, View*);
    virtual ~CardView();
    void setCard(std::shared_ptr<Card>, bool = true);

private:
    Model *model_;
    View *view_;
    Controller *controller_;
    std::shared_ptr<Card> card_;
    Gtk::Image *cardImage_;

    void cardButtonClicked();
};

#endif
