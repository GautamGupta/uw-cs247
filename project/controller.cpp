/**
 * Controller class. Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 */

#include "controller.h"
#include "main.h"
#include "model.h"
#include "player.h"
#include "computerplayer.h"
#include "humanplayer.h"
#include "card.h"
#include <stdlib.h>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

Controller::Controller(Model *m) : model_(m), rng(DEFAULT_SEED) {}

/**
 * Start the round
 * 1. If it's the first round, generate 52 cards. Otherwise use deck from previous round.
 * 2. Shuffle the deck
 * 3. Clear players' card arrays
 * 4. Assign cards to players in order (cards 0-12 go to player 1 etc)
 */
void Controller::startRound(Cards &cards) {
    Card startingCard(SPADE, SEVEN);

    shuffleCards(cards);

    // We must call this after getDeck()
    model_->startRound();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        Cards playerCards(cards.begin() + CARDS_PER_PLAYER * i, cards.begin() + CARDS_PER_PLAYER * (i+1));
        model_->addPlayerCards(i, playerCards);
        for (int j = 0; j < playerCards.size(); j++) {
            if (*(playerCards.at(j)) == startingCard) {
                model_->setCurrentPlayer(i);
            }
        }
    }

    // // TEST: DOES START ROUND WITH SEED WORK?
    // Cards deck = model_->getDeck();
    // for (int i = 0; i< deck.size(); i++){
    //     cout << *deck[i] << endl;
    // }

    // // TEST: CHECK PLAYERS' CARDS
    // for (int i = 0; i < NUM_PLAYERS; i++) {
    //     Cards currentCards = model_->getCurrentCards(i);
    //     cout << "Player " << i+1 << endl;
    //     for (int j = 0; j < currentCards.size(); j++){
    //         cout << *currentCards[j] << endl;
    //     }
    //     cout << endl;
    // }

    autoPlay();
}

/**
 * Shuffle cards based on seed
 */
void Controller::shuffleCards(Cards &cards) {
    int n = cards.size();

    while (n > 1) {
        int k = (int) (rng() % n);
        --n;
        shared_ptr<Card> card = cards[n];
        cards[n] = cards[k];
        cards[k] = card;
    }
}

/**
 * Play all computer plays until it's a human's turn to play
 */
void Controller::autoPlay() {
    int currentPlayer = model_->currentPlayer();
    while (!model_->isRoundOver() && !model_->isHuman(currentPlayer)) {
        cout << "Playing computer." << endl;
        playComputer(currentPlayer);
    }
}

/**
 * End the round. Checks if anyone scored > 80 pts and ends the game at that point.
 * Displays the winner if game is over otherwise starts a new round.
 */
void Controller::endRound() {
    model_->endRound();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        // view()->endRound(i, *model_->player(i));
    }

    if (model_->isGameOver()) {
        int lowestScore = model_->lowestScore();
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (model_->calculatePlayerScore(i) == lowestScore) {
                // view()->displayVictory(i);
            }
        }
    } else {
        Cards cards = model_->getDeck();
        startRound(cards);
    }
}

/**
 * Convert Human to Computer and play for computer
 */
void Controller::rageQuit(int playerNum) {
    togglePlayer(playerNum);
    playComputer(playerNum);
}

/**
 * Switch player type
 */
void Controller::togglePlayer(int playerNum) {
    if (model_->isHuman(playerNum)) {
        shared_ptr<Player> newPlayer(new ComputerPlayer(*model_->getPlayer(playerNum)));
        model_->replacePlayer(playerNum, newPlayer);
    } else {
        shared_ptr<Player> newPlayer(new HumanPlayer(*model_->getPlayer(playerNum)));
        model_->replacePlayer(playerNum, newPlayer);
    }
}

/**
 * Computer's turn to play. Play if there are legal plays else discard
 *
 * @param playerNum Player index
 */
void Controller::playComputer(int playerNum) {
    Cards legalPlays = model_->getLegalPlays(playerNum);

    // Play first card
    if (legalPlays.size() > 0) {
        model_->playCard(playerNum, *legalPlays.at(0));

    // Discard first card
    } else {
        Card card = *(model_->getCurrentCards(playerNum).at(0));
        model_->discardCard(playerNum, card);
    }
}

bool Controller::playHumanCard(int playerNum, Card card) {
    Cards legalPlays = model_->getLegalPlays(playerNum);

    for (int i = 0; i < legalPlays.size(); i++) {
        if (*legalPlays.at(i) == card) {
            try {
                model_->playCard(playerNum, card);
                autoPlay();
                return true;
            } catch (Player::CardNotFoundException &e) {
                exit(EXIT_FAILURE);
            }

            break;
        }
    }

    return false;
}

bool Controller::discardHumanCard(int playerNum, Card card) {
    Cards legalPlays = model_->getLegalPlays(playerNum);

    if (legalPlays.size() == 0) {
        try {
            model_->discardCard(playerNum, card);
            autoPlay();
            return true;
        } catch (Player::CardNotFoundException &e) {
            exit(EXIT_FAILURE);
        }
    }

    return false;
}

/**
 * Start a new game with seed
 *
 * (Re-)generate the cards, shuffle in starRound()
 */
void Controller::startButtonClicked(int seed /* = DEFAULT_SEED */) {
    cerr << "Start " << seed << endl;
    rng.seed(seed);

    Cards cards;

    for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
        for (int rank = ACE; rank < RANK_COUNT; rank++) {
            shared_ptr<Card> card(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
            cards.push_back(card);
        }
    }

    startRound(cards);
}

/**
 * End current game
 *
 * Player types are retained.
 */
void Controller::endButtonClicked() {
    cout << "End" << endl;
}
