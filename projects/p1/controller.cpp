/**
 * Controller class. Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 */

#include "controller.h"
#include "main.h"
#include "model.h"
#include "view.h"
#include "player.h"
#include "computerplayer.h"
#include "humanplayer.h"
#include "card.h"
#include "command.h"
#include <stdlib.h>
#include <string>
#include <cassert>
#include <iostream>
#include <random>

using namespace std;

Controller::Controller(Model *m, View *v) : model_(m), view_(v) {
    inputPlayers();
    startRound();
}

/* Get functions */

Model* Controller::model() {
    return model_;
}

View* Controller::view() {
    return view_;
}

void Controller::inputPlayers() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        string types = "hc";

        // Read in the type, make sure it's valid
        char type = view()->inputPlayer(i);
        PlayerType playerType = (PlayerType) types.find(type);
        assert(playerType != string::npos);

        switch (playerType) {
            case HUMAN: {
                shared_ptr<Player> humanPlayer(new HumanPlayer());
                model()->addPlayer(humanPlayer);
                break;
            }

            case COMPUTER: {
                shared_ptr<Player> computerPlayer(new ComputerPlayer());
                model()->addPlayer(computerPlayer);
                break;
            }

        }
    }
}

void Controller::assignCards() {
    vector< shared_ptr<Card> > cards;

    for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
        for (int rank = ACE; rank < RANK_COUNT; rank++) {
            shared_ptr<Card> card(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
            cards.push_back(card);
        }
    }

    shuffleCards(cards);

    Card startingCard(SPADE, SEVEN);

    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = CARDS_PER_PLAYER * i; j < CARDS_PER_PLAYER * (i+1); j++) {
            model()->addPlayerCard(i, cards.at(j));
            if (*(cards.at(j)) == startingCard) {
                model()->setStartPlayer(i);
            }
        }
    }
}

void Controller::shuffleCards(vector< shared_ptr<Card> > &cards) {
    static mt19937 rng(seed);

    int n = cards.size();

    while (n > 1) {
        int k = (int) (rng() % n);
        --n;
        shared_ptr<Card> card = cards[n];
        cards[n] = cards[k];
        cards[k] = card;
    }
}

void Controller::startRound() {
    model()->startRound();
    assignCards();

    int startPlayer = model()->startPlayer();
    view()->startRound(startPlayer);

    for (int i = 0; i < NUM_CARDS; i++) {
        int playerNum = (i + startPlayer) % NUM_PLAYERS;

        if (model()->player(playerNum)->isHuman()) {
            view()->displayCardsOnTable(model()->getSuitCardsOnTable());
            view()->displayHand(model()->player(playerNum)->getCurrentCards());
            view()->displayLegalPlays(model()->getLegalPlays(playerNum));
            playHuman(playerNum);
        } else {
            playComputer(playerNum);
        }
    }

    endRound();
}

void Controller::endRound() {
    model()->endRound();

    for (int i = 0; i < NUM_PLAYERS; i++) {
        view()->endRound(i, *model()->player(i));
    }

    if (model()->isGameOver()) {
        int lowestScore = model()->lowestScore();
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (model()->player(i)->calculateScore() == lowestScore) {
                view()->displayVictory(i);
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
                view()->errorPlayCard();
                return playHuman(playerNum);
            } else {
                try {
                    model()->player(playerNum)->playCard(command.card);
                } catch (Player::CardNotFoundException &e) {
                    exit(EXIT_FAILURE);
                }

                view()->displayPlayCard(playerNum + 1, command.card);
            }

            break;
        }

        case DISCARD : {
            if (legalPlays.size() > 0) {
                view()->errorDiscardCard();
                return playHuman(playerNum);
            }
            else {
                view()->displayDiscardCard(playerNum, command.card);
            }

            try {
                model()->player(playerNum)->discardCard(command.card);
            } catch (Player::CardNotFoundException &e) {
                exit(EXIT_FAILURE);
            }

            break;
        }

        case DECK :
            view()->displayCards(model()->getDeck());
            return playHuman(playerNum);

        case QUIT :
            return exit(EXIT_SUCCESS);

        case RAGEQUIT : {
            shared_ptr<Player> computerPlayer(new ComputerPlayer(*model()->player(playerNum)));
            model()->replacePlayer(playerNum, computerPlayer);

            view()->displayRageQuit(playerNum);
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
        view()->displayPlayCard(playerNum, *legalPlays.at(0));

    // Discard first card
    } else {
        Card card = *(model()->player(playerNum)->getCurrentCards().at(0));
        model()->player(playerNum)->discardCard(card);
        view()->displayDiscardCard(playerNum, card);
    }
}
