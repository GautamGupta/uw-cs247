/*
 * View class. Responsible for input/output.
 */

#ifndef ST_VIEW_H
#define ST_VIEW_H

class Model;

class View {
public:
    View( Model* );
	virtual ~View();
    Model* model();
    char inputPlayer(int);
    void startRound(int);

private:
	Model *model_;
}; // View

#endif
