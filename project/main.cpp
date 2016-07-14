/**
 * Straights Game
 *
 * Created by Bo Peng and Gautam Gupta
 */

#include "main.h"
#include "model.h"
#include "controller.h"
#include "view.h"
#include <gtkmm.h>

using namespace std;

/**
 * First called method
 */
int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);              // Initialize gtkmm with the command line arguments, as appropriate.
	Model model;                            // Create model
    Controller controller(&model);          // Create controller
    View view(&model, &controller);         // Create the view
    Gtk::Main::run(view);                   // Show the window and return when it is closed.

	return 0;
}
