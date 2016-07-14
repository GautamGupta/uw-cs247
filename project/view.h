/**
 * View class. Responsible for input/output.
 */

#ifndef ST_VIEW_H
#define ST_VIEW_H

/** Documentation of methods in .cpp file */

#include "main.h"
#include "card.h"
#include "player.h"
#include "observer.h"
#include "DeckGUI.h"
#include <gtkmm.h>
#include <vector>

class Model;
class Controller;
class PlayerView;
class CardView;

class View : public Gtk::Window, public Observer {
public:
    View(Model*, Controller*);
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

    void displayCards(std::vector<int>);
    void displayCards(Cards);

    void displayVictory(int);
    Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();
    Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card);
    void displayMessage(std::string title, std::string message);


private:
    // Observer Pattern: to access Model accessors without having to downcast subject
    Model *model_;
    Controller *controller_;

    // Card Images
    DeckGUI deck;

    // Boxes, frames, and tables
    Gtk::VBox masterContainer;
    Gtk::HBox gameBox; // Contains start game, seed, and end game buttons

    Gtk::Frame tableFrame; // Contains cards on table
    Gtk::Table cardsOnTable;
    Gtk::Image *cardsPlayed[SUIT_COUNT][RANK_COUNT];

    Gtk::HBox playerBox; // Contains Player ID, computer/human, score and discards
    PlayerView *playerViews[NUM_PLAYERS];

    Gtk::Frame playerHandFrame; // Contains player's hand

    Gtk::HBox playerHandBox;
    CardView *cardsInHand[CARDS_PER_PLAYER];

    Gtk::Button startButton_;
    Gtk::Button endButton_;

    Gtk::Entry seedInput_;

    // Signal handlers:
    void startButtonClicked();
    void endButtonClicked();

    // Update view functions
    void updateCardsOnTable();
    void updateCurrentHand();

    // Beep function
    void playBeep();
};

#endif
