/*
 * View class. Responsible for input/output.
 */

#ifndef ST_VIEW_H
#define ST_VIEW_H

#include "Card.h"
#include "Player.h"
#include <vector>

class Model;

class View {
public:
    View(Model*);
	virtual ~View();
    Model* model();

    char inputPlayer(int);

    void startRound(int);
    void endRound(int, Player);
    void displayDiscards(Cards);
    void displayCardsOnTable(SuitCards);
    void displayHand(Cards);
    void displayLegalPlays(Cards);
    void displayRageQuit(int);

    void displayCards(std::vector<Rank>);
    void displayCards(Cards);

    void displayVictory(int);

private:
	Model *model_;
}; // View

#endif
