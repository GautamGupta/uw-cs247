/*
 * View class. Responsible for input/output.
 */

#ifndef ST_VIEW_H
#define ST_VIEW_H

/** Documentation of methods in .cpp file */

#include "card.h"
#include "player.h"
#include "observer.h"
#include "DeckGUI.h"
#include <gtkmm.h>
#include <vector>

class Model;

class View : public Gtk::Window, public Observer {
public:
    View(Model*);
	~View();
    virtual void update();  // Observer Pattern: concrete update() method

    char inputPlayer(int);

    void startRound(int);
    void endRound(int, Player &);
    void displayCardsOnTable(SuitCards);
    void displayHand(Cards);
    void displayLegalPlays(Cards);
    void displayPlayCard(int, Card);
    void errorPlayCard();
    void displayDiscardCard(int, Card);
    void errorDiscardCard();
    void displayRageQuit(int);

    void displayCards(std::vector<int>);
    void displayCards(Cards);

    void displayVictory(int);

private:
    // Observer Pattern: to access Model accessors without having to downcast subject
    Model *model_;

    // Card Images
    DeckGUI deck;

    // Member widgets:
    Gtk::HBox panels;      // Main window divided into two horizontal panels
    Gtk::VBox butBox;      // Vertical boxes for stacking buttons vertically
    Gtk::Button next_button;
    Gtk::Button reset_button;
    Gtk::Image card;

    // Signal handlers:
    void nextButtonClicked();
    void resetButtonClicked();

}; // View

#endif
