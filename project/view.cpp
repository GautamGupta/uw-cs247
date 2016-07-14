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
#include <stdlib.h>
#include <algorithm>

using namespace std;

const string View::TXT_TITLE = "Straights";
const string View::TXT_ERROR = "Error";
const string View::TXT_START_BTN = "Start new game with seed:";
const string View::TXT_END_BTN = "End current game";
const string View::TXT_CARDS_ON_TABLE_LBL = "Cards on the table";
const string View::TXT_CURRENT_CARDS_LBL = "Your hand";

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
 * Start a new round
 */
void View::startRound(int playerNum) {
    cout << "A new round begins. It's player " << (playerNum + 1) << "'s turn to play." << endl;
}

/**
 * Display all discards and scores for round end
 */
void View::endRound(int playerNum, Player &player) {
    cout << "Player " << (playerNum + 1) << "'s discards: ";
    displayCards(player.getDiscardedCards());

    cout << "Player " << (playerNum + 1) << "'s score: "
        << player.getPreviousScore() << " + " << player.getScore()
        << " = " << (player.getPreviousScore() + player.getScore()) << endl;
}

/**
 * Show cards on table separated by suits for human play
 *
 * @param SuitCards Hashmap of Suit -> vector of cards
 */
void View::displayCardsOnTable(SuitCards suitCards) {
    cout << "Cards on the table:" << endl;

    // Order matters
    for (int suitNum = CLUB; suitNum < SUIT_COUNT; suitNum++) {
        Suit suit = static_cast<Suit>(suitNum);
        vector<int> ranks;

        for (int i = 0; i < suitCards[suit].size(); i++) {
            ranks.push_back((int) suitCards[suit].at(i)->getRank());
        }
        sort(ranks.begin(), ranks.end());

        switch (suit) {
            case CLUB :
                cout << "Clubs:";
                break;
            case DIAMOND :
                cout << "Diamonds:";
                break;
            case HEART :
                cout << "Hearts:";
                break;
            case SPADE :
                cout << "Spades:";
                break;

            default :
                break;
        }

        displayCards(ranks);
    }
}

void View::displayHand(Cards cards) {
    cout << "Your hand: ";
    string message = displayCards(cards);
    cout << message;
}

void View::displayLegalPlays(Cards cards) {
    cout << "Legal plays: ";
    string message = displayCards(cards);
    cout << message;
}

void View::displayPlayCard(int playerNum, Card card) {
    cout << "Player " << (playerNum + 1) << " plays " << card << "." << endl;
}

void View::errorPlayCard() {
    cout << "This is not a legal play." << endl;
}

void View::displayDiscardCard(int playerNum, Card card) {
    cout << "Player " << (playerNum + 1) << " discards " << card << "." << endl;
}

void View::errorDiscardCard() {
    cout << "You have a legal play. You may not discard." << endl;
}

/**
 * Displays ranks separated by space, followed by a newline
 */
void View::displayCards(vector<int> ranks) {
    for (int i = 0; i < ranks.size(); i++) {
        cout << " " << Card::getDisplayRank(ranks.at(i));
    }

    cout << endl;
}

/**
 * Displays cards 13 per line. Will print a newline even if there are no cards
 */
string View::displayCards(Cards cards) {
    string message = "";
    for (int i = 0; i < cards.size(); i++) {
        message += Card::getDisplayRank(cards.at(i)->getRank()) +Card::getDisplaySuit(cards.at(i)->getSuit());

        // Newline at the end of 13 cards (mainly for deck_) / end of list
        if ((i+1) % CARDS_PER_PLAYER == 0 || (i+1) == cards.size()) {
            message += "\n";
        } else {
            message += " ";
        }
    }

    // Next line if no cards
    if (cards.size() == 0) {
        message+="\n";
    }
    return message;
}

void View::displayVictory(int playerNum) {
    cout << "Player " << (playerNum + 1) << " wins!" << endl;
}

void View::update() {
    updateCardsOnTable();
    updateCurrentHand();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        playerViews_[i]->update();
    }

    if (model_->didRoundJustStart() && model_->getCurrentPlayer() != -1) {
        string message = "Player " + to_string(model_->getCurrentPlayer() + 1) + "'s turn to play.";
        displayMessage("New Round", message);

        model_->roundJustStarted();
    }
    if (model_->isRoundOver()){
        string message;
        for (int i = 0; i < NUM_PLAYERS; i++){
            // display player discards
            message += "Player " + to_string(i+1) + "'s discards: ";
            Cards discardedCards = model_->getPlayerDiscardedCards(i);
            message += displayCards(discardedCards);

            // display player score
            message += "Player " + to_string(i+1) + "'s score: ";
            message += to_string(model_->getPlayerPreviousScore(i)) + " + " + to_string(model_->getPlayerScore(i)) + " = " + to_string(model_->getPlayerTotalScore(i));
            message += "\n\n";
        }

        displayMessage("End Round", message);
    }

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

void View::startButtonClicked() {
    int seed = atoi(seedInput_.get_text().c_str());
    if (!seed) {
        seed = DEFAULT_SEED;
    }

    controller_->startButtonClicked(seed);
}

void View::endButtonClicked() {
    controller_->endButtonClicked();
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
 * Update the current hand displayed for human player's view
 */
void View::updateCurrentHand() {
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

Glib::RefPtr<Gdk::Pixbuf> View::getNullCardImage() {
    return deck_.getNullCardImage();
}

Glib::RefPtr<Gdk::Pixbuf> View::getCardImage(Card card) {
    return deck_.getCardImage(card);
}

/**
 * Displays a pop up dialogue with a title and message
 */
void View::displayMessage(string title, string message) {
    Gtk::MessageDialog dialogue(*this, title);
    dialogue.set_secondary_text(message);
    dialogue.run();
}
