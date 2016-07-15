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
    static const std::string TXT_TITLE;
    static const std::string TXT_ERROR;
    static const std::string TXT_START_BTN;
    static const std::string TXT_END_BTN;
    static const std::string TXT_CARDS_ON_TABLE_LBL;
    static const std::string TXT_CURRENT_CARDS_LBL;
    static const std::string TXT_NEW_ROUND;
    static const std::string TXT_END_ROUND;
    static const std::string TXT_END_GAME;
    static const std::string TXT_PLAYER_TURN;
    static const std::string TXT_PLAYER_DISCARDS;
    static const std::string TXT_PLAYER_SCORE;
    static const std::string TXT_PLAYER_WINS;

    View(Model*, Controller*);
    ~View();
    void update(); // Observer Pattern: concrete update() method

    Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();
    Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card);
    void displayDialogue(std::string title, std::string message);

    static std::string _sprintf(std::string, int);

private:
    // Observer Pattern: to access Model accessors without having to downcast subject
    Model *model_;
    Controller *controller_;

    // Card Images
    DeckGUI deck_;

    // Master vertical container, 4 rows
    Gtk::VBox masterBox_;

    // Row 1: Horizontal - start game btn, seed text, end game btn
    Gtk::HBox gameBox_;
    Gtk::Button startButton_;
    Gtk::Entry seedInput_;
    Gtk::Button endButton_;

    // Row 2: 4 rows x 13 cols table - 52 cards on table
    Gtk::Frame cardsOnTableFrame_;
    Gtk::Table cardsOnTableTable_;
    Gtk::Image *cardsOnTable_[SUIT_COUNT][RANK_COUNT];

    // Row 3: Horizontal - 4 players (id, computer/human/rage, score, discards)
    Gtk::HBox playerBox_;
    PlayerView *playerViews_[NUM_PLAYERS];

    // Row 4: Horizontal - player's hand, 13 cards
    Gtk::Frame currentCardsFrame_;
    Gtk::HBox currentCardsBox_;
    CardView *currentCards_[CARDS_PER_PLAYER];

    void startButtonClicked();
    void endButtonClicked();

    void updateGameBox();
    void updateCardsOnTable();
    void updatePlayerViews();
    void updateCurrentCards();
    void displayMessages();

    std::string displayCards(Cards);
};

#endif
