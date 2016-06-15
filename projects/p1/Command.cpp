#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;

istream &operator>>(istream &in, Command &c){
	c.type = BAD_COMMAND;
	
	string str;
	getline(in, str);
	stringstream ss(str);
	
	string cmd;
	ss >> cmd;
	
	if (cmd == "play") {
		c.type = PLAY;
		ss >> c.card;
	} else if (cmd == "discard") {
		c.type = DISCARD;
		ss >> c.card;
	} else if (cmd == "deck") {
		c.type = DECK;
	} else if (cmd == "quit") {
		c.type = QUIT;
	} else if (cmd == "ragequit") {
		c.type = RAGEQUIT;
	}
	
	assert(!in.fail() && !ss.fail() && c.type != BAD_COMMAND);
	
	return in;
}
