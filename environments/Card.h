
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
	tDimond = 2,
	tClub = 3
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

/* Create a mapping from card to int in the following matter:
    "2c": 1,
    "2d": 2,
    "2h": 3,
    "2s": 4,
    "3c": 5,
    "3d": 6,
    "3h": 7,
    "3s": 8,
    "4c": 9,
    "4d": 10,
    "4h": 11,
    "4s": 12,
    "5c": 13,
    "5d": 14,
    "5h": 15,
    "5s": 16,
    "6c": 17,
    "6d": 18,
    "6h": 19,
    "6s": 20,
    "7c": 21,
    "7d": 22,
    "7h": 23,
    "7s": 24,
    "8c": 25,
    "8d": 26,
    "8h": 27,
    "8s": 28,
    "9c": 29,
    "9d": 30,
    "9h": 31,
    "9s": 32,
    "tc": 33,
    "td": 34,
    "th": 35,
    "ts": 36,
    "jc": 37,
    "jd": 38,
    "jh": 39,
    "js": 40,
    "qc": 41,
    "qd": 42,
    "qh": 43,
    "qs": 44,
    "kc": 45,
    "kd": 46,
    "kh": 47,
    "ks": 48,
    "ac": 49,
    "ad": 50,
    "ah": 51,
    "as": 52
  */
int Card_to_int(Card c);

//reverse function of card_to_int
Card Int_to_card(int n);

#endif //!CARD_H