/**
 * To ensure that the your cards are ordered the same way as
 * the given program, use this shuffling algorithm.
 *
 * NUM_CARDS is the constant 52
 * cards_ is an array of pointers to cards
 */

#include "main.h"
#include "card.h"
#include <random>
#include <vector>

using namespace std;

void shuffle(vector<Card*> cards_) {
    static mt19937 rng(seed);

	int n = NUM_CARDS;

	while (n > 1) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}
