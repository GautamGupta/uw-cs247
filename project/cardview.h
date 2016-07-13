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
	void updateCard();

private:
	Model* model_;
	View* view_;
	Controller* controller_;
    Gtk::Image* cardImage;
    void cardButtonClicked();

};

#endif
