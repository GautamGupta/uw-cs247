/**
 * Straights Game
 *
 * Created by Bo Peng and Gautam Gupta
 */

#include "model.h"
#include "controller.h"
#include "view.h"

const int NUM_PLAYERS = 4;

int main(int argc, char* argv[]) {
	Model model;                            // Create model
    View view(&model);                      // Create the view -- is passed handle model
    Controller controller(&model, &view);   // Create controller -- is passed handle to view and model

    controller.start();

	return 0;
}
