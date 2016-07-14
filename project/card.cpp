#include "card.h"
#include <string>

using namespace std;

/**
 * Generate a new card given suit and rank
 */
Card::Card(Suit s, Rank r) {
	suit_ = s;
	rank_ = r;
}

Card::~Card() {}

Suit Card::getSuit() const {
	return suit_;
}

Rank Card::getRank() const {
	return rank_;
}

/**
 * Get display char for particular suit
 */
string Card::getDisplaySuit(int suit) {
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	return suits[suit];
}

/**
 * Get display char for particular rank
 */
string Card::getDisplayRank(int rank) {
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	return ranks[rank];
}

/**
 * Check if two cards have same suit and rank
 */
bool operator==(const Card &a, const Card &b) {
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

/**
 * Output a card <rank><suit> like 7S
 */
ostream &operator<<(ostream &out, const Card &c) {
	out << Card::getDisplayRank(c.getRank()) << Card::getDisplaySuit(c.getSuit());
	return out;
}
