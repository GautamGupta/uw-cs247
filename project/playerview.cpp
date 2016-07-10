#include "playerview.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include <gtkmm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

const string PlayerView::TXT_HUMAN = "Human";
const string PlayerView::TXT_COMPUTER = "Computer";
const string PlayerView::TXT_RAGE = "Rage!";
const string PlayerView::TXT_POINTS = "%d points";
const string PlayerView::TXT_DISCARDS = "%d points";
const string PlayerView::TXT_PLAYER = "Player %d";

PlayerView::PlayerView(Model* model, Controller* controller, View* view, int playerNum) :
        model_(model), controller_(controller), view_(view), playerNum_(playerNum) {

    char playerText[TXT_PLAYER.length()];
    sprintf(playerText, TXT_PLAYER.c_str(), playerNum_+1);
    set_label(playerText);
    setLabels();

    container.pack_start(toggleBtn);
    container.pack_start(pointsTxt);
    container.pack_end(discardsTxt);
    add(container);

    // sets button label based on player type in model
    if (model_->player(playerNum_)->isHuman()) {
        setToggleButton(TXT_HUMAN, true);
    } else {
        setToggleButton(TXT_COMPUTER, true);
    }

    // connect click event to event handler
    toggleBtn.signal_clicked().connect(sigc::mem_fun(*this, &PlayerView::onBtnClick));
}

PlayerView::~PlayerView() {}

Model* PlayerView::model() {
    return model_;
}

Controller* PlayerView::controller() {
    return controller_;
}

View* PlayerView::view() {
    return view_;
}

/**
 * Update label text, defaults to 0's
 */
void PlayerView::setLabels(int score /* = 0 */, int discards /* = 0 */) {
    char pointsText[TXT_POINTS.length()], discardsText[TXT_DISCARDS.length()];
    sprintf(pointsText, TXT_POINTS.c_str(), score);
    sprintf(discardsText, TXT_DISCARDS.c_str(), discards);

    pointsTxt.set_label(pointsText);
    discardsTxt.set_label(discardsText);
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
    // Ragequit
    if (toggleBtn.get_label() == TXT_RAGE) {
        setToggleButton(TXT_RAGE, false);
        controller()->playerRageQuit(playerNum_);

    // Toggle Human <-> Computer
    } else {
        toggleBtn.set_label((toggleBtn.get_label() == TXT_HUMAN) ? TXT_COMPUTER : TXT_HUMAN);
        // controller()->toggleBtn(playerNum_);
    }
}

/**
 * Update with new points and discard counts
 */
void PlayerView::update() {
    // TODO: Add logic
    int points = 0;
    int discards = 0;

    setLabels(points, discards);
}
