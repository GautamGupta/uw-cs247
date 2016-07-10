/**
 * View class. Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 */

#include "main.h"
#include "view.h"
#include "model.h"
#include "controller.h"
#include "card.h"
#include "observer.h"
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

View::View(Model *model, Controller *controller) :
        model_(model), controller_(controller), panels(true, 10), butBox(true, 10),
        startButton_("Start new game with seed:"), endButton_("End current game"), card(deck.null()) {

	// Sets some properties of the window.
  set_title("Straights");
	set_border_width(10);

	// Add panels to the window
  add(masterContainer);

	card.set( deck.null() );

  // Set up containers
  masterContainer.pack_start(gameBox);
  masterContainer.pack_start(tableFrame);
  masterContainer.pack_start(playerBox);

  // Set up gameBox
  gameBox.pack_start( startButton_ );
  gameBox.pack_start( seedInput_ );
  gameBox.pack_end( endButton_ );
            
    // Uncomment later
    // seedInput_.set_text(intToString(_model->getSeed()));

  // UI for gameBox
  startButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::startButtonClicked ) );
  endButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::endButtonClicked ) );
  seedInput_.signal_changed().connect( sigc::mem_fun( *this, &View::seedInputted ) );

  // UI for cards on table
  tableFrame.set_label("Cards on the table");
  tableFrame.add(cardsOnTable);
  cardsOnTable.set_row_spacings(5);

  // Coming soon
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      // cardsPlayed[i][j] = new Gtk::Image(nullCardPixbuf);
      // cardsOnTable.attach(*cardsPlayed[i][j], j, j+1, i, i+1);
    }
  }

  // UI for playerBox
  // for (int i = 0; i < 4; i++) {
  //   playerViews[i] = new PlayerView(i+1, _model, this, _controller);
  //   playersContainer.pack_start(*playerViews[i]);
  // }


	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

}

View::~View() {}

Model* View::model() {
    return model_;
}

Controller* View::controller() {
    return controller_;
}

/**
 * Take in h/c to define if a player is human or computer
 */
char View::inputPlayer(int playerNum) {
    char type;

    cout << "Is player " << (playerNum + 1) << " a human(h) or a computer(c)?" << endl;
    cout << ">";
    cin >> type;
    assert ( !cin.fail() );

    return type;
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
    displayCards(cards);
}

void View::displayLegalPlays(Cards cards) {
    cout << "Legal plays: ";
    displayCards(cards);
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

void View::displayRageQuit(int playerNum) {
    cout << "Player " << (playerNum + 1) << " ragequits. A computer will now take over." << endl;
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
void View::displayCards(Cards cards) {
    for (int i = 0; i < cards.size(); i++) {
        cout << *cards.at(i);

        // Newline at the end of 13 cards (mainly for deck) / end of list
        if ((i+1) % CARDS_PER_PLAYER == 0 || (i+1) == cards.size()) {
            cout << endl;
        } else {
            cout << " ";
        }
    }

    // Next line if no cards
    if (cards.size() == 0) {
        cout << endl;
    }
}

void View::displayVictory(int playerNum) {
    cout << "Player " << (playerNum + 1) << " wins!" << endl;
}

void View::update() {
    card.set(deck.null());
}

void View::startButtonClicked() {
    controller()->startButtonClicked();
    cout << " AY LMAO " << endl;
}

void View::endButtonClicked() {
    controller()->endButtonClicked();
    cout << " Reach Chen's " << endl;
}

void View::seedInputted(){
    cout << " I Just entered a seed" << endl;
}
