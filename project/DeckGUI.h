/**
 * Loads a series of pixmaps used for displaying the cards, as well as a card back used as a place marker in the
 * display when we don't have a card yet to display. Use pixel buffers to share images since widgets cannot be
 * shared.
 */

#ifndef __DECK_GUI_H
#define __DECK_GUI_H
#include <gdkmm/pixbuf.h>
#include <vector>

#include "card.h"

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Rank, Suit);       // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();                 // Returns the image to use for the placeholder.


private:
	std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck;   // Contains the pixel buffer images.
};

#endif
