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
#include <string>
#include <cassert>
#include <iostream>
#include <random>

using namespace std;

Controller::Controller(Model *m, View *v) : model_(m), view_(v) {
    inputPlayers();
    assignCards();
}

/* Get functions */

Model* Controller::model() {
    return model_;
}

View* Controller::view() {
    return view_;
}

void Controller::inputPlayers() {
    for (int i = 1; i <= NUM_PLAYERS; i++) {
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

    for (int suit = CLUB; suit != SPADE; suit++) {
        for (int rank = ACE; rank != KING; rank++) {
            shared_ptr<Card> card(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
            cards.push_back(card);
        }
    }

    shuffleCards(cards);
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
