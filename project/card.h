#ifndef _CARD_
#define _CARD_

#include <memory>
#include <vector>
#include <map>

/** Documentation of methods in .cpp file */

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
            EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card {
public:
    Card(Suit, Rank);
    virtual ~Card();

    Suit getSuit() const;
    Rank getRank() const;
    std::string getDisplay() const;

    static std::string getDisplaySuit(int);
    static std::string getDisplayRank(int);

private:
    Suit suit_;
    Rank rank_;
};

bool operator==(const Card &, const Card &);

typedef std::vector< std::shared_ptr< Card > > Cards;
typedef std::map< Suit, Cards > SuitCards;

#endif
