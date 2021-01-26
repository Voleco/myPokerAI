
#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <algorithm>
#include <string>
#include<map>
#include <ctime>
#include <utility>
#include<stdint.h>
#include"Deck.h"
#include"Action.h"
#include"../utils/RankingCombinations.h"

//total number of entries in the lookup table (== 52 choose 5)
#define TOTAL_NUM_ENTRIES_52C5 2598960

using std::string;
using std::vector;
using std::map;
using std::cout;


enum HandTypeEnum {
	t_Royal_Flush         = 9,
	t_Straight_Flush      = 8, 
	t_Four_of_a_Kind      = 7, 
	t_Full_Houses         = 6, 
	t_Flush               = 5, 
	t_Straight            = 4, 
	t_Three_of_a_Kind     = 3, 
	t_Two_Pair            = 2, 
	t_One_Pair            = 1,  
	t_High_Card           = 0 
};

std::ostream& operator <<(std::ostream& out, const HandTypeEnum& h);

class HandEvaluator
{
public:
	HandEvaluator() 
	{
	}
	HandEvaluator(const char* prefix) 
	{
		if(!LoadTableFromFile(prefix))
		{
			 BuildTable();
			 SaveTableToFile(prefix);
		}

	}
	~HandEvaluator() 
	{
	}

	/*
	build a DAT file of 2598960 entries so that:
	each entry stores the hand value of
	a combination of 5 cards
	and the index of that entry is the rank of the 5 cards
	*/
	void BuildTable();
	
	/*
	load the DAT file into memory for query
	*/
	bool LoadTableFromFile(const char *prefix);

	bool SaveTableToFile(const char *prefix);

	/*
	query the handvalue of 5 cards
	*/
	uint16_t GetHandValue_5_Cards(Card c1, Card c2, Card c3, Card c4, Card c5);
	uint16_t GetHandValue_6_Cards(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6);
	uint16_t GetHandValue_7_Cards(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7);

private:

	vector<uint16_t> handValueLookupTable;
};



#endif // !EVALUATOR_H


