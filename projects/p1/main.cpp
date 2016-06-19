/**
 * Straights Game
 *
 * Created by Bo Peng and Gautam Gupta
 */

#include "main.h"
#include "model.h"
#include "controller.h"
#include "view.h"

int main(int argc, char* argv[]) {
	Model model;                            // Create model
    View view(&model);                      // Create the view -- is passed handle model
    Controller controller(&model, &view);   // Create controller -- is passed handle to view and model

	return 0;
}
