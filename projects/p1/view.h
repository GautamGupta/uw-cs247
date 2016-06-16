/*
 * View class. Responsible for input/output.
 */


#ifndef ST_VIEW_H
#define ST_VIEW_H

#include "observer.h"

class Controller;
class Model;


class View : public Observer {
public:
    View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;

	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Signal handlers:
	void nextButtonClicked();
	void resetButtonClicked();

}; // View

#endif
