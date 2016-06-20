#ifndef _CARD_
#define _CARD_

#include <istream>
#include <ostream>
#include <tr1/memory>
#include <vector>
#include <map>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card {
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;

    static std::string getDisplaySuit(int);
    static std::string getDisplayRank(int);

private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

typedef std::vector< std:tr1::shared_ptr< Card > > Cards;
typedef std::map< Suit, Cards > SuitCards;

#endif
