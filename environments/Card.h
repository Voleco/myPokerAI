
#ifndef CARD_H
#define CARD_H


#include <string>
#include <iostream>
#include <fstream>
#include <string.h>

using std::string;

enum Suit {
	tSpade = 0,
	tHeart = 1,
	tClub = 2,
	tDimond = 3
};

Suit Str_to_suit(string sStr);

enum Rank {
	tRank2 = 2,
	tRank3 = 3,
	tRank4 = 4,
	tRank5 = 5,
	tRank6 = 6,
	tRank7 = 7,
	tRank8 = 8,
	tRank9 = 9,
	tRankT = 10,
	tRankJ = 11,
	tRankQ = 12,
	tRankK = 13,
	tRankA = 14
};


string RankSuit_to_str(Rank r, Suit s);

Rank Str_to_rank(string rStr);

class Card
{
public:
	Card() {}
	Card(Suit _suit, Rank _rank)
	{
		s = _suit;
		r = _rank;
		cardStr = RankSuit_to_str(r, s);
	}
	Card(string _cardStr)
	{
		cardStr = _cardStr;
		r = Str_to_rank(cardStr.substr(0, 1));
		s = Str_to_suit(cardStr.substr(1, 2));
	}

	Rank r;
	Suit s;
	string cardStr;
	friend std::ostream& operator <<(std::ostream& out, const Card& c);
};

#endif //!CARD_H