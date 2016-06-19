/*
 * View class. Responsible for input/output.
 */

#ifndef ST_VIEW_H
#define ST_VIEW_H

#include "Card.h"
#include <vector>

class Model;

class View {
public:
    View(Model*);
	virtual ~View();
    Model* model();
    char inputPlayer(int);
    void startRound(int);
    void displayCardsOnTable(SuitCards);
    void displayHand(Cards);

    void displayCards(std::vector<Rank>);
    void displayCards(Cards);

private:
	Model *model_;
}; // View

#endif
