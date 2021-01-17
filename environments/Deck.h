
#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include"Card.h"


using std::string;
using std::vector;

static string NORMALHAND[52] =
{
	"2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks","As",
	"2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh","Ah",
	"2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc","Ac",
	"2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd","Ad"
};

class Deck
{
public:
	Deck() {}
	Deck(unsigned int size);
	void ShuffleCards();
	Card GetNthCard(unsigned int index);
	unsigned int GetDeckSize() { return deckSize; }
	friend std::ostream& operator <<(std::ostream& out, const Deck& d);
private:
	vector<Card> cards;
	unsigned int deckSize;
};

Deck::Deck(unsigned int size)
{
	cards.resize(0);
	deckSize = size;
	if (deckSize == 52)
	{
		for (int i = 0; i < 52; i++)
			cards.push_back(Card(NORMALHAND[i]));
	}
}

void Deck::ShuffleCards()
{
	unsigned seed = 0;
	//seed = unsigned(std::time(0));
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card Deck::GetNthCard(unsigned int index)
{
	return cards[index];
}

std::ostream& operator <<(std::ostream& out, const Deck& d)
{
	for (unsigned int i=0;i<d.deckSize;i++)
		out << d.cards[i]<<" ";
	return out;
}

#endif // !DECK_H


