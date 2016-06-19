/**
 * Controller class. Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 */

#include "controller.h"
#include "main.h"
#include "model.h"
#include "view.h"
#include "player.h"
#include <string>
#include <cassert>

using namespace std;

Controller::Controller(Model *m, View *v) : model_(m), view_(v) {
    inputPlayers();
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

        shared_ptr<Player> player(new Player());

        /* switch (playerType) {
            case HUMAN:
                player = new Player();
                break;

            case COMPUTER:
                player = new Player();
                break;

        } */

        model()->addPlayer(player);
    }
}
