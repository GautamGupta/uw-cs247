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
    while (!model_->isRoundOver() && !model_->isPlayerHuman(model_->getCurrentPlayer())) {
        playComputer(model_->getCurrentPlayer());
    }
}

/**
 * End the round. Checks if anyone scored > 80 pts and ends the game at that point.
 * Displays the winner if game is over otherwise starts a new round.
 */
void Controller::endRound() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        // view()->endRound(i, *model_->player(i));
    }

    if (model_->isGameOver()) {
        int getLowestPlayerScore = model_->getLowestPlayerScore();
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (model_->getPlayerTotalScore(i) == getLowestPlayerScore) {
                // view()->displayVictory(i);
            }
        }
        model_->reset();
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
    autoPlay();
}

/**
 * Switch player type
 */
void Controller::togglePlayer(int playerNum) {
    model_->togglePlayer(playerNum);
}

/**
 * Computer's turn to play. Play if there are legal plays else discard
 *
 * @param playerNum Player index
 */
void Controller::playComputer(int playerNum) {
    Cards legalPlays = model_->getPlayerLegalPlays(playerNum);

    // Play first card
    if (legalPlays.size() > 0) {
        model_->playCard(playerNum, *legalPlays.at(0));

    // Discard first card
    } else {
        Card card = *(model_->getPlayerCurrentCards(playerNum).at(0));
        model_->discardCard(playerNum, card);
    }
}

void Controller::playHuman(int playerNum, Card card) {
    Cards legalPlays = model_->getPlayerLegalPlays(playerNum);

    if (legalPlays.size() == 0) {
        model_->discardCard(playerNum, card);
        autoPlay();
    } else {
        for (int i = 0; i < legalPlays.size(); i++) {
            if (*legalPlays.at(i) == card) {
                model_->playCard(playerNum, card);
                autoPlay();
                return;
            }
        }

        // Card not in legal plays
        throw Controller::InvalidPlayException();
    }
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
    cerr << "End" << endl;
    model_->reset();
}
