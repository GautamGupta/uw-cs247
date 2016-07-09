/**
 * Straights Game
 *
 * Created by Bo Peng and Gautam Gupta
 */

#include "main.h"
#include "model.h"
#include "controller.h"
#include "view.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * For shuffling
 */
int seed = 0;

/**
 * First called method
 */
int main(int argc, char* argv[]) {
    // Set seed if it was supplied
	if (argc > 1) {
		seed = atoi(argv[1]);
	}

	Model model;                            // Create model
    View view;                              // Create the view
    Controller controller(&model, &view);   // Create controller -- is passed handle to view and model

	return 0;
}
