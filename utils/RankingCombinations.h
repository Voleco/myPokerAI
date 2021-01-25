
#ifndef RANKINGCOMBINATIONS_H
#define RANKINGCOMBINATIONS_H


#include <iostream>
#include <vector>
#include <stdint.h>


/*
reference:
https://computationalcombinatorics.wordpress.com/2012/09/10/ranking-and-unranking-of-combinations-and-permutations/
using lex-co order
*/


class RankingCombination {
public:

    RankingCombination(){}
    //input: an array of size k (items)
    //output: the rank of this combination in (N choose k)
	uint64_t Rank(int *items, int k, int N) const;

    //input: a uint64_t number representing the rank of the combinations in (N choose k) 
    //output: set up the numbers in arrar(items) correctly accroding to the rank
	void Unrank(uint64_t hash, int *items, int k, int N) const;

    uint64_t NChooseK(int N, int k) const;



};


#endif //!RANKINGCOMBINATIONS_H