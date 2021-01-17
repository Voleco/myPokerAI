
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

Suit Str_to_suit(string sStr)
{
	Suit s = tSpade;
	if (sStr == "s")
		s = tSpade;
	else if (sStr == "h")
		s = tHeart;
	else if (sStr == "c")
		s = tClub;
	else if (sStr == "d")
		s = tDimond;

	return s;
}



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


string RankSuit_to_str(Rank r, Suit s)
{
	string str = "";
	switch (r)
	{
	case tRank2:
		str = "2";
		break;
	case tRank3:
		str = "3";
		break;
	case tRank4:
		str = "4";
		break;
	case tRank5:
		str = "5";
		break;
	case tRank6:
		str = "6";
		break;
	case tRank7:
		str = "7";
		break;
	case tRank8:
		str = "8";
		break;
	case tRank9:
		str = "9";
		break;
	case tRankT:
		str = "T";
		break;
	case tRankJ:
		str = "J";
		break;
	case tRankQ:
		str = "Q";
		break;
	case tRankK:
		str = "K";
		break;
	case tRankA:
		str = "A";
		break;
	default:
		break;
	}
	switch (s)
	{
	case tSpade:
		str += "s";
		break;
	case tHeart:
		str += "h";
		break;
	case tClub:
		str += "c";
		break;
	case tDimond:
		str += "d";
		break;
	default:
		break;
	}
	return str;
}

Rank Str_to_rank(string rStr)
{
	Rank r = tRankA;
	if (rStr == "2")
		r=tRank2;
	else if (rStr == "3")
		r = tRank3;
	else if (rStr == "4")
		r = tRank4;
	else if (rStr == "5")
		r = tRank5;
	else if (rStr == "6")
		r = tRank6;
	else if (rStr == "7")
		r = tRank7;
	else if (rStr == "8")
		r = tRank8;
	else if (rStr == "9")
		r = tRank9;
	else if (rStr == "T")
		r = tRankT;
	else if (rStr == "J")
		r = tRankJ;
	else if (rStr == "Q")
		r = tRankQ;
	else if (rStr == "K")
		r = tRankK;
	else if (rStr == "A")
		r = tRankA;

	return r;
}

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


std::ostream& operator <<(std::ostream& out, const Card& c)
{
	out << c.cardStr;
	return out;
}

#endif //!CARD_H