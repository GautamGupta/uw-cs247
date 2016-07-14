#include "playerview.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include <gtkmm.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

namespace {
    string _sprintf(string text, int num) {
        char cText[text.length()];
        sprintf(cText, text.c_str(), num);
        return string(cText);
    }
}

const string PlayerView::TXT_HUMAN = "Human";
const string PlayerView::TXT_COMPUTER = "Computer";
const string PlayerView::TXT_RAGE = "Rage!";
const string PlayerView::TXT_SCORE = "Score: %d";
const string PlayerView::TXT_DISCARDS = "%d discards";
const string PlayerView::TXT_PLAYER = "Player %d";
const string PlayerView::TXT_RAGE_MSG = "Player %d ragequits. A computer will now take over.";

PlayerView::PlayerView(Model* model, Controller* controller, View* view, int playerNum) :
        model_(model), controller_(controller), view_(view), playerNum_(playerNum) {
    set_label(_sprintf(TXT_PLAYER, playerNum_+1));

    container.pack_start(toggleBtn);
    container.pack_start(scoreTxt);
    container.pack_end(discardsTxt);
    add(container);

    // connect click event to event handler
    toggleBtn.signal_clicked().connect(sigc::mem_fun(*this, &PlayerView::onBtnClick));

    update();
}

PlayerView::~PlayerView() {}

/**
 * Update label text, defaults to 0's
 */
void PlayerView::setLabels(int score /* = 0 */, int discards /* = 0 */) {
    scoreTxt.set_label(_sprintf(TXT_SCORE, score));
    discardsTxt.set_label(_sprintf(TXT_DISCARDS, discards));
}

/**
 * Set button with text and enable/disable
 */
void PlayerView::setToggleButton(string text, bool sensitive) {
    toggleBtn.set_sensitive(sensitive);
    toggleBtn.set_label(text);
}

/**
 * Handles
 *  1. Human / Computer toggle before gameplay
 *  2. Ragequit during gameplay
 */
void PlayerView::onBtnClick() {
    // Rage quit
    if (toggleBtn.get_label() == TXT_RAGE) {
        controller_->rageQuit(playerNum_);
        cout << _sprintf(TXT_RAGE_MSG, playerNum_+1) << endl;

    // Toggle Human <-> Computer
    } else {
        controller_->togglePlayer(playerNum_);
    }
}

/**
 * Update with new score and discard counts
 */
void PlayerView::update() {
    int score = model_->getPlayerScore(playerNum_);
    int discards = model_->getPlayerDiscardedCards(playerNum_).size();
    setLabels(score, discards);

    if (model_->isGameInProgress()) {
        if (model_->isHuman(playerNum_)) {
            bool enabled = (model_->currentPlayer() == playerNum_);
            setToggleButton(TXT_RAGE, enabled);
        } else {
            setToggleButton(TXT_COMPUTER, false);
        }
    } else {
        if (model_->isHuman(playerNum_)) {
            setToggleButton(TXT_HUMAN, true);
        } else {
            setToggleButton(TXT_COMPUTER, true);
        }
    }
}
