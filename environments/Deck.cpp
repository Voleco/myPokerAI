
#include"Deck.h"


using std::string;
using std::vector;


Deck::Deck(unsigned int size)
{
	nextCardPos = 0;
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
	seed = unsigned(std::time(0));
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	nextCardPos = 0;
}

Card Deck::GetNthCard(unsigned int index)
{
	return cards[index];
}

Card Deck::DealOneCard()
{
	Card res = cards[nextCardPos];
	nextCardPos++;
	return res;
}

std::ostream& operator <<(std::ostream& out, const Deck& d)
{
	for (unsigned int i=0;i<d.deckSize;i++)
		out << d.cards[i]<<" ";
	return out;
}
