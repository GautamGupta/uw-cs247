/**
 * View class. Responsible for input / output.
 */

#include "main.h"
#include "view.h"
#include "model.h"
#include "controller.h"
#include "card.h"
#include "observer.h"
#include "playerview.h"
#include "cardview.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>

using namespace std;

const string View::TXT_TITLE = "Straights";
const string View::TXT_ERROR = "Error";
const string View::TXT_START_BTN = "Start new game with seed:";
const string View::TXT_END_BTN = "End current game";
const string View::TXT_CARDS_ON_TABLE_LBL = "Cards on the table";
const string View::TXT_CURRENT_CARDS_LBL = "Your hand";
const string View::TXT_NEW_ROUND = "New Round";
const string View::TXT_END_ROUND = "Round Ends";
const string View::TXT_END_GAME = "Game Over";
const string View::TXT_PLAYER_TURN = "Player %d's turn to play.";
const string View::TXT_PLAYER_DISCARDS = "Player %d discards: ";
const string View::TXT_PLAYER_SCORE = "Player %d score: ";
const string View::TXT_PLAYER_WINS = "Player %d wins!";

View::View(Model *model, Controller *controller) :
        model_(model), controller_(controller),
        startButton_(TXT_START_BTN), endButton_(TXT_END_BTN) {

    // Sets some properties of the window.
    set_title(TXT_TITLE);
    set_border_width(10);

    // Master vertical container, 4 rows
    add(masterBox_);
    masterBox_.pack_start(gameBox_);
    masterBox_.pack_start(cardsOnTableFrame_);
    masterBox_.pack_start(playerBox_);
    masterBox_.pack_start(currentCardsFrame_);

    // Row 1: Horizontal - start game btn, seed text, end game btn
    startButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::startButtonClicked));
    endButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::endButtonClicked));
    seedInput_.set_text(to_string(DEFAULT_SEED));
    gameBox_.pack_start(startButton_);
    gameBox_.pack_start(seedInput_);
    gameBox_.pack_end(endButton_);

    // Row 2: 4 rows x 13 cols table - 52 cards on table
    cardsOnTableFrame_.set_label(TXT_CARDS_ON_TABLE_LBL);
    cardsOnTableFrame_.add(cardsOnTableTable_);
    cardsOnTableTable_.set_row_spacings(5);
    cardsOnTableTable_.set_col_spacings(5);
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            cardsOnTable_[i][j] = new Gtk::Image(getNullCardImage());
            cardsOnTableTable_.attach(*cardsOnTable_[i][j], j, j+1, i, i+1);
        }
    }

    // Row 3: Horizontal - 4 players (id, computer/human/rage, score, discards)
    for (int i = 0; i < NUM_PLAYERS; i++) {
        playerViews_[i] = new PlayerView(model_, controller_, this, i);
        playerBox_.pack_start(*playerViews_[i]);
    }

    // Row 4: Horizontal - player's hand, 13 cards
    currentCardsFrame_.add(currentCardsBox_);
    currentCardsFrame_.set_label(TXT_CURRENT_CARDS_LBL);
    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        currentCards_[i] = new CardView(model_, controller_, this);
        currentCardsBox_.add(*currentCards_[i]);
    }

    // The final step is to display the buttons (they display themselves)
    show_all();

    // Register view as observer of model
    model_->subscribe(this);

    update();
}

/**
 * Destructor
 */
View::~View() {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            delete cardsOnTable_[i][j];
        }
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
        delete playerViews_[i];
    }

    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        delete currentCards_[i];
    }
}

/**
 * Get the seed and start game
 */
void View::startButtonClicked() {
    int seed = atoi(seedInput_.get_text().c_str());
    if (!seed) {
        seed = DEFAULT_SEED;
    }

    controller_->startButtonClicked(seed);
}

/**
 * Reset model, end game
 */
void View::endButtonClicked() {
    controller_->endButtonClicked();
}

/**
 * Return string of cards 13 per line.
 * Will return a newline even if there are no cards
 */
string View::displayCards(Cards cards) {
    string message;

    for (int i = 0; i < cards.size(); i++) {
        message += cards.at(i)->getDisplay();

        // Newline at the end of 13 cards (mainly for deck_) / end of list
        if ((i+1) % CARDS_PER_PLAYER == 0 || (i+1) == cards.size()) {
            message += "\n";
        } else {
            message += " ";
        }
    }

    // Newline if no cards
    if (cards.size() == 0) {
        message += "\n";
    }

    return message;
}

void View::update() {
    updateGameBox();
    updateCardsOnTable();
    updateCurrentCards();
    updatePlayerViews();
    displayMessages();
}

/**
 * Enable / Disable buttons / text input when apt
 */
void View::updateGameBox() {
    if (model_->isGameInProgress()) {
        startButton_.set_sensitive(false);
        seedInput_.set_sensitive(false);
        endButton_.set_sensitive(true);
    } else {
        startButton_.set_sensitive(true);
        seedInput_.set_sensitive(true);
        endButton_.set_sensitive(false);
    }
}

/**
 * Update the view with cards played
 */
void View::updateCardsOnTable() {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            cardsOnTable_[i][j]->set(getNullCardImage());
        }
    }

    Cards cards = model_->getCardsOnTable();
    for (int i = 0; i < cards.size(); i++) {
        Card card = *cards.at(i);
        cardsOnTable_[card.getSuit()][card.getRank()]->set(getCardImage(card));
    }
}

/**
 * Update the 4 player views with score / discards
 */
void View::updatePlayerViews() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        playerViews_[i]->update();
    }
}

/**
 * Update the current hand displayed for human player's view
 */
void View::updateCurrentCards() {
    Cards cards, legalPlays;

    if (model_->isGameInProgress() && model_->isPlayerHuman(model_->getCurrentPlayer())) {
        cards = model_->getPlayerCurrentCards(model_->getCurrentPlayer());
        legalPlays = model_->getPlayerLegalPlays(model_->getCurrentPlayer());
    } else {
        cards = Cards();
        legalPlays = Cards();
    }

    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        if (i >= cards.size()) {
            currentCards_[i]->setCard(NULL, false);
        } else {
            bool enabled = (legalPlays.size() == 0);
            // Order of cards matters
            for (int j = 0; j < legalPlays.size(); j++) {
                if (*cards.at(i) == *legalPlays.at(j)) {
                    enabled = true;
                    break;
                }
            }
            currentCards_[i]->setCard(cards.at(i), enabled);
        }
    }
}

/**
 * Display dialogues when appropriate
 */
void View::displayMessages() {
    string message;

    // On round start
    if (model_->isRoundStarting()) {
        message = _sprintf(TXT_PLAYER_TURN, model_->getCurrentPlayer() + 1) + "\n";
        displayDialogue(TXT_NEW_ROUND, message);

    // On round end
    } else if (model_->isRoundOver()) {
        for (int i = 0; i < NUM_PLAYERS; i++){
            // Player discards
            message += _sprintf(TXT_PLAYER_DISCARDS, i+1);
            Cards discardedCards = model_->getPlayerDiscardedCards(i);
            message += displayCards(discardedCards);

            // Player score
            message += _sprintf(TXT_PLAYER_SCORE, i+1);
            message += to_string(model_->getPlayerPreviousScore(i)) + " + " + to_string(model_->getPlayerScore(i)) + " = " + to_string(model_->getPlayerTotalScore(i));
            message += "\n\n";
        }

        displayDialogue(TXT_END_ROUND, message);

        // On game end
        if (model_->isGameOver()) {
            int lowestPlayerScore = model_->getLowestPlayerScore();
            message = "";
            for (int i = 0; i < NUM_PLAYERS; i++) {
                if (model_->getPlayerTotalScore(i) == lowestPlayerScore) {
                    message += _sprintf(TXT_PLAYER_WINS, i+1) + "\n";
                }
            }
            displayDialogue(TXT_END_GAME, message);
        }
    }
}

/**
 * Get null card image
 */
Glib::RefPtr<Gdk::Pixbuf> View::getNullCardImage() {
    return deck_.getNullCardImage();
}

/**
 * Get image for specified card
 */
Glib::RefPtr<Gdk::Pixbuf> View::getCardImage(Card card) {
    return deck_.getCardImage(card);
}

/**
 * Displays a pop up dialogue with a title and message
 * Also send to cout
 */
void View::displayDialogue(string title, string message) {
    cout << title << endl;
    cout << message;

    Gtk::MessageDialog dialogue(*this, title);
    dialogue.set_secondary_text(message);
    dialogue.run();
}

/**
 * Custom sprintf with length constraint and 1 parameter
 */
string View::_sprintf(string text, int num) {
    char cText[text.length()];
    sprintf(cText, text.c_str(), num);
    return string(cText);
}
