#ifndef _COMMAND_
#define _COMMAND_

#include "card.h"
#include <istream>

/** Documentation of methods in .cpp file */

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command {
	Type type;
	Card card;

	Command() : type(BAD_COMMAND), card(SPADE, ACE) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif
