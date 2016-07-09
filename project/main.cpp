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
#include <gtkmm/main.h>

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

    Gtk::Main kit(argc, argv);              // Initialize gtkmm with the command line arguments, as appropriate.
	Model model;                            // Create model
    View view(&model);                      // Create the view
    Controller controller(&model, &view);   // Create controller -- is passed handle to view and model
    Gtk::Main::run(view);                   // Show the window and return when it is closed.

	return 0;
}
