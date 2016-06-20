#include "command.h"
#include <iostream>
#include <cassert>

using namespace std;

istream &operator>>(istream &in, Command &c) {
	c.type = BAD_COMMAND;

	cout << ">";
	string cmd;
	cin >> cmd;

	if (cmd == "play") {
		c.type = PLAY;
		cin >> c.card;
	} else if (cmd == "discard") {
		c.type = DISCARD;
		cin >> c.card;
	} else if (cmd == "deck") {
		c.type = DECK;
	} else if (cmd == "quit") {
		c.type = QUIT;
	} else if (cmd == "ragequit") {
		c.type = RAGEQUIT;
	}

	assert(!in.fail() && c.type != BAD_COMMAND);

	return in;
}
