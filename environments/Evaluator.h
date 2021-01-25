
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


using std::string;
using std::vector;
using std::map;
using std::cout;


enum HandType {
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

class HandEvaluator
{
public:
	HandEvaluator() {}

	/*
	build a DAT file of 2598960 entries so that:
	each entry stores the hand value of
	a combination of 5 cards
	and the index of that entry is the rank of the 5 cards
	*/
	void BuildDATFile();
	
	/*
	load the DAT file into memory for query
	*/
	bool LoadDATFlie();

	/*
	query the handvalue of 5 cards
	*/
	uint64_t HandValue(Card c1, Card c2, Card c3, Card c4, Card c5);

private:

};



#endif // !EVALUATOR_H


