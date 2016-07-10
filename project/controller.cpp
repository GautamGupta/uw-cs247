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
#include "command.h"
#include <stdlib.h>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

Controller::Controller(Model *m) : model_(m), rng(DEFAULT_SEED) {}

/**
 * Get model
 */
Model* Controller::model() {
    return model_;
}

/**
 * 1. If it's the first round, generate 52 cards. Otherwise use deck from previous round.
 * 2. Shuffle the deck
 * 3. Clear players' arrays
 * 4. Assign cards to players in order (cards 0-12 go to player 1 etc)
 */
void Controller::assignCards() {
    vector< shared_ptr<Card> > cards = model()->getDeck();
    if (cards.size() == 0) {
        for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
            for (int rank = ACE; rank < RANK_COUNT; rank++) {
                shared_ptr<Card> card(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
                cards.push_back(card);
            }
        }
    }

    shuffleCards(cards);

    Card startingCard(SPADE, SEVEN);

    for (int i = 0; i < NUM_PLAYERS; i++) {
        model()->player(i)->startRound();
        for (int j = CARDS_PER_PLAYER * i; j < CARDS_PER_PLAYER * (i+1); j++) {
            model()->addPlayerCard(i, cards.at(j));
            if (*(cards.at(j)) == startingCard) {
                model()->setStartPlayer(i);
            }
        }
    }
}

/**
 * Shuffle cards based on seed
 */
void Controller::shuffleCards(vector< shared_ptr<Card> > &cards) {
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
 * Start the round. Assign cards and do 52 plays (for 52 cards).
 */
void Controller::startRound() {
    // model()->startRound();
    assignCards();

    int startPlayer = model()->startPlayer();
    // view()->startRound(startPlayer);

    for (int i = 0; i < NUM_CARDS; i++) {
        int playerNum = (i + startPlayer) % NUM_PLAYERS;

        if (model()->player(playerNum)->isHuman()) {
            // view()->displayCardsOnTable(model()->getSuitCardsOnTable());
            // view()->displayHand(model()->player(playerNum)->getCurrentCards());
            // view()->displayLegalPlays(model()->getLegalPlays(playerNum));
            playHuman(playerNum);
        } else {
            playComputer(playerNum);
        }
    }

    endRound();
}

/**
 * End the round. Checks if anyone scored > 80 pts and ends the game at that point.
 * Displays the winner if game is over otherwise starts a new round.
 */
void Controller::endRound() {
    model()->endRound();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        // view()->endRound(i, *model()->player(i));
    }

    if (model()->isGameOver()) {
        int lowestScore = model()->lowestScore();
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (model()->player(i)->calculateScore() == lowestScore) {
                // view()->displayVictory(i);
            }
        }
    } else {
        startRound();
    }
}

/**
 * Human's turn to play. Get input and perform the play
 *
 * @param playerNum Player index
 */
void Controller::playHuman(int playerNum) {
    Cards legalPlays = model()->getLegalPlays(playerNum);

    Command command;
    cin >> command;

    switch (command.type) {
        case PLAY : {
            bool canPlay = false;
            for (int i = 0; i < legalPlays.size(); i++) {
                if (*legalPlays.at(i) == command.card) {
                    canPlay = true;
                    break;
                }
            }

            if (!canPlay) {
                // view()->errorPlayCard();
                return playHuman(playerNum);
            } else {
                try {
                    model()->player(playerNum)->playCard(command.card);
                } catch (Player::CardNotFoundException &e) {
                    exit(EXIT_FAILURE);
                }

                // view()->displayPlayCard(playerNum, command.card);
            }

            break;
        }

        case DISCARD : {
            if (legalPlays.size() > 0) {
                // view()->errorDiscardCard();
                return playHuman(playerNum);
            }

            try {
                model()->player(playerNum)->discardCard(command.card);
                // view()->displayDiscardCard(playerNum, command.card);
            } catch (Player::CardNotFoundException &e) {
                exit(EXIT_FAILURE);
            }

            break;
        }

        case DECK :
            // view()->displayCards(model()->getDeck());
            return playHuman(playerNum);

        case QUIT :
            return exit(EXIT_SUCCESS);

        case RAGEQUIT : {
            shared_ptr<Player> computerPlayer(new ComputerPlayer(*model()->player(playerNum)));
            model()->replacePlayer(playerNum, computerPlayer);

            // view()->displayRageQuit(playerNum);
            return playComputer(playerNum);
        }

        default :
            return exit(EXIT_FAILURE);
    }

}

/**
 * Computer's turn to play. Play if there are legal plays else discard
 *
 * @param playerNum Player index
 */
void Controller::playComputer(int playerNum) {
    Cards legalPlays = model()->getLegalPlays(playerNum);

    // Play first card
    if (legalPlays.size() > 0) {
        model()->player(playerNum)->playCard(*legalPlays.at(0));
        // view()->displayPlayCard(playerNum, *legalPlays.at(0));

    // Discard first card
    } else {
        Card card = *(model()->player(playerNum)->getCurrentCards().at(0));
        model()->player(playerNum)->discardCard(card);
        // view()->displayDiscardCard(playerNum, card);
    }
}

/**
 * Start a new game with seed
 */
void Controller::startButtonClicked(int seed /* = DEFAULT_SEED */) {
    cout << "Start " << seed << endl;
    rng.seed(seed);
    assignCards();
}

/**
 * End current game
 *
 * Player types are retained.
 */
void Controller::endButtonClicked() {
    cout << "End" << endl;
}
