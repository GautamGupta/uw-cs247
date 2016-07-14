/**
 * Controller class. Responsible for translating UI events (from the View)
 * into method calls to the Model.
 */

#include "controller.h"
#include "main.h"
#include "model.h"
#include "player.h"
#include "card.h"
#include <stdlib.h>
#include <string>

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

    if (!model_->isPlayerHuman(model_->getCurrentPlayer())) {
        playComputer(model_->getCurrentPlayer());
    }
}

/**
 * Computer's turn to play. Play if there are legal plays else discard
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

    doneTurn();
}

/**
 * Play the specified card for human
 */
void Controller::playHuman(int playerNum, Card card) {
    Cards legalPlays = model_->getPlayerLegalPlays(playerNum);

    if (legalPlays.size() == 0) {
        model_->discardCard(playerNum, card);
        doneTurn();
    } else {
        for (int i = 0; i < legalPlays.size(); i++) {
            if (*legalPlays.at(i) == card) {
                model_->playCard(playerNum, card);
                doneTurn();
                return;
            }
        }

        // Card not in legal plays
        throw Controller::InvalidPlayException();
    }
}

/**
 * 1. Checks if the round is over (52 cards played / discarded)
 *     1.1 Checks if anyone scored > 80 pts and ends the game at that point.
 *     1.2 Starts a new round otherwise
 * 2. If the new player is a computer, play for computer
 */
void Controller::doneTurn() {
    if (model_->isRoundOver()) {
        if (model_->isGameOver()) {
            int lowestPlayerScore = model_->getLowestPlayerScore();
            for (int i = 0; i < NUM_PLAYERS; i++) {
                if (model_->getPlayerTotalScore(i) == lowestPlayerScore) {
                    // view()->displayVictory(i);
                }
            }
            model_->reset();
        } else {
            Cards cards = model_->getDeck();
            startRound(cards);
        }
    } else if (!model_->isPlayerHuman(model_->getCurrentPlayer())) {
        playComputer(model_->getCurrentPlayer());
    }
}

/**
 * Convert Human to Computer and play for computer
 */
void Controller::rageQuit(int playerNum) {
    togglePlayer(playerNum);
    playComputer(model_->getCurrentPlayer());
}

/**
 * Switch player type
 */
void Controller::togglePlayer(int playerNum) {
    model_->togglePlayer(playerNum);
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
 * Start a new game with seed
 *
 * (Re-)generate the cards, shuffle in starRound()
 */
void Controller::startButtonClicked(int seed /* = DEFAULT_SEED */) {
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
    model_->reset();
}
