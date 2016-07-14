#ifndef __DECK_GUI_H
#define __DECK_GUI_H
#include <gtkmm.h>
#include <vector>
#include "card.h"

/** Documentation of methods in .cpp file */

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
    Glib::RefPtr<Gdk::Pixbuf> getCardImage(Suit, Rank);
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card);
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();

private:
	std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck;
};

#endif
