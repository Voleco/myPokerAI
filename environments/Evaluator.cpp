#include "Evaluator.h"

/*
Hand_Value/Unique/Distinct
Straight_Flush     40     10
Four_of_a_Kind    624    156  (13 choose 2)*(2 choose 1)
Full_Houses      3744    156  (13 choose 2)*(2 choose 1)
Flush            5108   1277  (13 choose 5)-10
Straight        10200     10   
Three_of_a_Kind 54912    858  (13 choose 3)*(3 choose 1)
Two_Pair       123552    858  (13 choose 3)*(3 choose 1)
One_Pair      1098240   2860  (13 choose 4)*(4 choose 1)
High_Card     1302540   1277  (13 choose 5)-10
TOTAL         2598960   7462

handvalue: 16bits
0000|0000,0000,0000
First 4 bits: hand type
Royal_Flush         9         0x9000
Straight_Flush      8         0x8000
Four_of_a_Kind      7         0x7000
Full_Houses         6         0x6000
Flush               5         0x5000
Straight            4         0x4000
Three_of_a_Kind     3         0x3000
Two_Pair            2         0x2000
One_Pair            1         0x1000
High_Card           0         0x0000
*/

void HandEvaluator::BuildTable()
{
	cout << "start building the lookup table\n";
	RankingCombination rc;
	handValueLookupTable.resize(TOTAL_NUM_ENTRIES_52C5);

	int *cards_int = new int[5];
	Card *cards = new Card[5];

	//storing the number of entries for each tpye,
	vector<int> entryCounts;
	for (int i = 0; i < 10; i++)
	{
		entryCounts.push_back(0);
	}

	for (int x = 0; x < TOTAL_NUM_ENTRIES_52C5; x++)
	{
		if (x % 250000 == 0)
		{
			cout << x << " entries (out of 2598960) calculated\n";
		}

		uint64_t hash = (uint64_t)(x);
		uint16_t handVal = 0;
		rc.Unrank(hash, cards_int, 5, 52);
		//now we get a hand of 5 cards, sorting in accending order

		for (int i = 0; i < 5; i++)
			cards[i] = Int_to_card(cards_int[i] + 1);

		vector<int> ranks;
		vector<int> suits;
		vector<int> distinct_ranks;
		for (int i = 0; i < 5; i++)
		{
			int card_rank = static_cast<int>(cards[i].r);
			ranks.push_back(card_rank);
			suits.push_back(static_cast<int>(cards[i].s));

			bool exist = false;
			for (const auto &item : distinct_ranks)
				if (item == card_rank)
				{
					exist = true;
					break;
				}
			if (!exist)
				distinct_ranks.push_back(card_rank);
		}

		//the size of distinct_ranks tells us the hand type
		//size == 5: High card, Straight, Flush, SF, RF
		//size == 4: One pair
		//size == 3: Two pairs, Three of a Kind
		//size == 2: Full house, Four of a kind

		if (distinct_ranks.size() == 2) //Full house, Four of a kind
		{
			//main part and kicker
			int m, k;
			if (ranks[0] != ranks[1]) // kmmmm, four of a kind
			{
				m = ranks[1] - 2;
				k = ranks[0] - 2;
				handVal = handVal | 0x7000;
				handVal += m * 12 + k;
			}
			else if (ranks[1] != ranks[2]) //kkmmm, full house
			{
				m = ranks[2] - 2;
				k = ranks[1] - 2;
				handVal = handVal | 0x6000;
				handVal += m * 12 + k;
			}
			else if (ranks[2] != ranks[3]) //mmmkk, full house
			{
				m = ranks[2] - 2;
				k = ranks[3] - 2;
				handVal = handVal | 0x6000;
				handVal += m * 12 + k - 1;
			}
			else //mmmmk, four of a kind
			{
				m = ranks[3] - 2;
				k = ranks[4] - 2;
				handVal = handVal | 0x7000;
				handVal += m * 12 + k - 1;
			}
		}
		else if (distinct_ranks.size() == 3) //Two pairs, Three of a Kind
		{
			//for 3-of-a-kind, main part and 2 kickers; for 2 pairs, pair1, pair2 and kicker
			int m, k1, k2;
			if (ranks[0] != ranks[1])
			{
				if (ranks[1] != ranks[2]) //abccc, Three of a Kind
				{
					m = ranks[4] - 2;
					k1 = ranks[1] - 2;
					k2 = ranks[0] - 2;
					handVal = handVal | 0x3000;
				}
				else if (ranks[2] == ranks[3]) //abbbc, Three of a Kind
				{
					m = ranks[1] - 2;
					k1 = ranks[4] - 2;
					k2 = ranks[0] - 2;
					handVal = handVal | 0x3000;
				}
				else //abbcc,Two pairs
				{
					m = ranks[4] - 2;
					k1 = ranks[1] - 2;
					k2 = ranks[0] - 2;
					handVal = handVal | 0x2000;
				}
			}
			else if (ranks[1] != ranks[2])
			{
				if (ranks[2] != ranks[3]) //aabcc,Two pairs
				{
					m = ranks[4] - 2;
					k1 = ranks[0] - 2;
					k2 = ranks[2] - 2;
					handVal = handVal | 0x2000;
				}
				else //aabbc,Two pairs
				{
					m = ranks[2] - 2;
					k1 = ranks[0] - 2;
					k2 = ranks[4] - 2;
					handVal = handVal | 0x2000;
				}
			}
			else //aaabc, Three of a Kind
			{
				m = ranks[0] - 2;
				k1 = ranks[4] - 2;
				k2 = ranks[3] - 2;
				handVal = handVal | 0x3000;
			}
			if (handVal == 0x3000)
			{
				//for each triple, there exist (12 choose 2) combinations (from 12 remainling cards pick 2 kickers)
				handVal += m * rc.NChooseK(12, 2);
				if (k1 > m)
					k1--;
				if (k2 > m)
					k2--;
				for (int j = 1; j < k1; j++)
					handVal += rc.NChooseK(j, 1);
				handVal += k2;
			}
			if (handVal == 0x2000)
			{
				//for a pair of m, there exist (m choose 2) 2-pair combinations that both 2 pairs smaller than m
				//e.g. there are (12 choose 2) 2pairs smaller than AA223
				//each 2pairs can result in 11 hands (11 different kickers)
				handVal += rc.NChooseK(m, 2) * 11;
				if (k2 > m)
					k2--;
				if (k2 > k1)
					k2--;
				handVal += k1 * 11;
				handVal += k2;
			}
		}
		else if (distinct_ranks.size() == 4) //One pair
		{
			//the index of the pair. e.g. index==1 <=> abbcd type
			int index = 0;

			//main part(a pair) and 3 kickers
			int m=0, k1=0, k2=0, k3=0;
			for (int j = 0; j < 5; j++)
			{
				if (ranks[j] == ranks[j + 1])
				{
					index = j;
					break;
				}
			}
			switch (index)
			{
			case 0:
				m = ranks[0] - 2;
				k1 = ranks[4] - 2;
				k2 = ranks[3] - 2;
				k3 = ranks[2] - 2;
				break;
			case 1:
				m = ranks[1] - 2;
				k1 = ranks[4] - 2;
				k2 = ranks[3] - 2;
				k3 = ranks[0] - 2;
				break;
			case 2:
				m = ranks[2] - 2;
				k1 = ranks[4] - 2;
				k2 = ranks[1] - 2;
				k3 = ranks[0] - 2;
				break;
			case 3:
				m = ranks[4] - 2;
				k1 = ranks[2] - 2;
				k2 = ranks[1] - 2;
				k3 = ranks[0] - 2;
				break;
			default:
				//this should never happen
				break;
			}
			handVal = handVal | 0x1000;

			//for a pair of m, there exist (m choose 1) one-pair combinations that the pair smaller than m
			//e.g. there are (12 choose 1) onepair smaller than AAxxx
			//each onepair can result in (12 choose 3) hands (3 different kickers)
			handVal += m * rc.NChooseK(12, 3);
			if (k1 > m)
				k1--;
			if (k2 > m)
				k2--;
			if (k3 > m)
				k3--;

			handVal += rc.NChooseK(k1, 3);
			handVal += rc.NChooseK(k2, 2);
			handVal += rc.NChooseK(k3, 1);
		}
		else if (distinct_ranks.size() == 5) //High card, Flush, Straight, SF, RF
		{
			bool is_flush = false;
			bool is_straight = false;

			//determine whether it is straight of A,2,3,4,5
			bool straight_A = false;
			if (suits[0] == suits[1] && suits[0] == suits[2] && suits[0] == suits[3] && suits[0] == suits[4])
				is_flush = true;

			if (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5 && ranks[4] == 14)
				straight_A = true;
			if ((ranks[0] == ranks[1] - 1 && ranks[0] == ranks[2] - 2 && ranks[0] == ranks[3] - 3 && ranks[0] == ranks[4] - 4) || straight_A)
				is_straight = true;


			uint16_t value = 0;

			/*
6 High            4  choose 4       1
7 High            5  choose 4       5
...
A High           12  choose 4      495
*/
			//lets say this hand is Ahigh. we need to count the total number of 6-high, 7-high, ... K-high

			for (int j = 4; j >= 0; j--)
			{
				for (int k = j; k < ranks[j] - 2; k++)
				{
					value += rc.NChooseK(k, j);
				}
			}

			if (is_flush == true && is_straight == true)
			{
				if (value == 1286) //RF
				{
					handVal = 0x9000;
					handVal += value;
				}
				else //SF
				{
					handVal = 0x8000;
					if (straight_A)
						handVal += 5;
					else
						handVal += ranks[4];
				}
			}
			else if (is_flush == true && is_straight == false) //Flush
			{
				handVal = 0x5000;
				handVal += value;
			}
			else if (is_flush == false && is_straight == true) //Straight
			{
				handVal = 0x4000;
				if (straight_A)
					handVal += 5;
				else
					handVal += ranks[4];
			}
			else //High Card
			{
				handVal = 0x0000;
				handVal += value;
			}
		}

		handValueLookupTable[x] = handVal;

		uint16_t handType = handVal & 0xF000;
		handType = handType >> 12;
		entryCounts[handType]++;
	}

	cout << "******Lookup Table built***********\n";

	//validation, just to print out some information

	map<uint16_t, int> handValMap;

	for (int i = 0; i < TOTAL_NUM_ENTRIES_52C5; i++)
	{
		if (handValMap.find(handValueLookupTable[i]) != handValMap.end())
			handValMap[handValueLookupTable[i]]++;
		else
			handValMap[handValueLookupTable[i]] = 1;
	}

	cout << "Total number of distinct handvalue: " << handValMap.size() << "\n";

	vector<int> counts;
	for (int i = 0; i < 10; i++)
	{
		counts.push_back(0);
	}
	for (auto it = handValMap.begin(); it != handValMap.end(); it++)
	{
		uint16_t handType = it->first & 0xF000;
		handType = handType >> 12;
		//if(handType == 8)
		//	cout<<"sf value: "<<std::hex<<it->first<<"\n";
		counts[handType]++;
	}

	cout << "Number of distinct handvalue of each type:\n";
	for (int i = 9; i >= 0; i--)
	{
		cout << static_cast<HandTypeEnum>(i) << " :\t" << counts[i] << "\n";
	}
	cout << "Distribution of handtype from all possible 5-card combinations:\n";
	for (int i = 9; i >= 0; i--)
	{
		cout << static_cast<HandTypeEnum>(i) << " : entryCounts\t" << entryCounts[i] << "\n";
	}

}

bool HandEvaluator::LoadTableFromFile(const char *prefix)
{
	string fileName="";
	fileName += prefix;

	if (fileName.back() != '/')
		fileName += "/";
	fileName += "HandValueLookupTable.dat";

	FILE *f = fopen(fileName.c_str(), "rb");
	if (f == 0)
	{
		cout << "Error: could not load Lookuptable, fail to open: " << fileName << "\n";
		return false;
	}
	fseek(f, 0, SEEK_END);
	uint64_t fileSize= ftell(f);
	rewind(f);
	if (fileSize != sizeof(uint16_t)*TOTAL_NUM_ENTRIES_52C5)
	{
		cout << "Error: could not load Lookuptable, unmatched file size: " << fileName << " \n";
		return false;
	}
		
	uint16_t* data = new uint16_t[TOTAL_NUM_ENTRIES_52C5];
	uint64_t numEleRead = fread(data, sizeof(uint16_t), TOTAL_NUM_ENTRIES_52C5, f);
	if ( numEleRead != TOTAL_NUM_ENTRIES_52C5)
	{
		cout<<"numEleRead: "<<numEleRead<<"\n";
		cout << "Error: could not load Lookuptable, unable to read the whole file: " << fileName << "\n";
		return false;
	}
	fclose(f);
	handValueLookupTable = std::vector<uint16_t>(data,data+TOTAL_NUM_ENTRIES_52C5);
	cout << "Successfully loaded LookupTable from file: " << fileName << "\n";

	return true;
}

bool HandEvaluator::SaveTableToFile(const char *prefix)
{
	string fileName="";
	fileName += prefix;

	if (fileName.back() != '/')
		fileName += "/";
	fileName += "HandValueLookupTable.dat";

	FILE *f = fopen(fileName.c_str(), "wb");	

	fwrite(handValueLookupTable.data(), sizeof(uint16_t), TOTAL_NUM_ENTRIES_52C5, f);
	fclose(f);
	cout << "Saved LookupTable to: " << fileName << "\n";

	return true;
}

uint16_t HandEvaluator::GetHandValue_5_Cards(Card c1, Card c2, Card c3, Card c4, Card c5)
{
	vector<int> cards_int;
	cards_int.resize(5);
	cards_int[0] = Card_to_int(c1)-1;
	cards_int[1] = Card_to_int(c2)-1;
	cards_int[2] = Card_to_int(c3)-1;
	cards_int[3] = Card_to_int(c4)-1;
	cards_int[4] = Card_to_int(c5)-1;
	std::sort(cards_int.begin(),cards_int.end());

	RankingCombination rc;
	uint64_t rank = rc.Rank(cards_int.data(),5,52);

	return handValueLookupTable[rank];

}

uint16_t HandEvaluator::GetHandValue_6_Cards(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6)
{

	vector<Card> original_cards;
	original_cards.push_back(c1);
	original_cards.push_back(c2);
	original_cards.push_back(c3);
	original_cards.push_back(c4);
	original_cards.push_back(c5);
	original_cards.push_back(c6);

	//total number of hands from 6 cards
	//6 choose 5 == 6 
	int combos[6][5] =
	{
		{ 0, 1, 2, 3, 4},
		{ 0, 1, 2, 3, 5},
		{ 0, 1, 2, 4, 5},
		{ 0, 1, 3, 4, 5},
		{ 0, 2, 3, 4, 5},
		{ 1, 2, 3, 4, 5}
	};
	vector<uint16_t> results;
	results.resize(6);
	for(int i=0;i<6;i++)
	{
		results[i] = GetHandValue_5_Cards(original_cards[combos[i][0]],original_cards[combos[i][1]],original_cards[combos[i][2]],original_cards[combos[i][3]],
		original_cards[combos[i][4]]);
	}

	int best_combo_index = 0;
	uint16_t best_handVal = results[0];
	for(int i=0;i<6;i++)
	{
		if(results[i]>best_handVal)
		{
			best_combo_index = i;
			best_handVal = results[i];
		}
	}

	cout<<"best hand(5 cards) out of 6 cards: "<<original_cards[combos[best_combo_index][0]]<<original_cards[combos[best_combo_index][1]]
	<<original_cards[combos[best_combo_index][2]]<<original_cards[combos[best_combo_index][3]]<<original_cards[combos[best_combo_index][4]]<<"\n";
	return best_handVal;
}

uint16_t HandEvaluator::GetHandValue_7_Cards(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7)
{
	vector<Card> original_cards;
	original_cards.push_back(c1);
	original_cards.push_back(c2);
	original_cards.push_back(c3);
	original_cards.push_back(c4);
	original_cards.push_back(c5);
	original_cards.push_back(c6);
	original_cards.push_back(c7);


	//total number of hands from 7 cards
	//7 choose 5 == 21 

	int combos[21][5] =
	{
		{ 0, 1, 2, 3, 4},
		{ 0, 1, 2, 3, 5},
		{ 0, 1, 2, 4, 5},
		{ 0, 1, 3, 4, 5},
		{ 0, 2, 3, 4, 5},
		{ 1, 2, 3, 4, 5},
		{ 0, 1, 2, 3, 6},
		{ 0, 1, 2, 4, 6},
		{ 0, 1, 3, 4, 6},
		{ 0, 2, 3, 4, 6},
		{ 1, 2, 3, 4, 6},
		{ 0, 1, 2, 5, 6},
		{ 0, 1, 3, 5, 6},
		{ 0, 2, 3, 5, 6},
		{ 1, 2, 3, 5, 6},
		{ 0, 1, 4, 5, 6},
		{ 0, 2, 4, 5, 6},
		{ 1, 2, 4, 5, 6},
		{ 0, 3, 4, 5, 6},
		{ 1, 3, 4, 5, 6},
		{ 2, 3, 4, 5, 6}
	};
	vector<uint16_t> results;
	results.resize(21);
	for(int i=0;i<21;i++)
	{
		results[i] = GetHandValue_5_Cards(original_cards[combos[i][0]],original_cards[combos[i][1]],original_cards[combos[i][2]],original_cards[combos[i][3]],
		original_cards[combos[i][4]]);
	}

	int best_combo_index = 0;
	uint16_t best_handVal = results[0];
	for(int i=0;i<21;i++)
	{
		if(results[i]>best_handVal)
		{
			best_combo_index = i;
			best_handVal = results[i];
		}
	}

	cout<<"best hand(5 cards) out of 7 cards: "<<original_cards[combos[best_combo_index][0]]<<original_cards[combos[best_combo_index][1]]
	<<original_cards[combos[best_combo_index][2]]<<original_cards[combos[best_combo_index][3]]<<original_cards[combos[best_combo_index][4]]<<"\n";
	return best_handVal;
}

std::ostream &operator<<(std::ostream &out, const HandTypeEnum &h)
{
	switch (h)
	{
	case t_Royal_Flush:
		out << "Royal_Flush";
		break;
	case t_Straight_Flush:
		out << "Straight_Flush";
		break;
	case t_Four_of_a_Kind:
		out << "Four_of_A_Kind";
		break;
	case t_Full_Houses:
		out << "Full_House";
		break;
	case t_Flush:
		out << "Flush";
		break;
	case t_Straight:
		out << "Straight";
		break;
	case t_Three_of_a_Kind:
		out << "Three_of_A_Kind";
		break;
	case t_Two_Pair:
		out << "Two_Pair";
		break;
	case t_One_Pair:
		out << "One_Pair";
		break;
	case t_High_Card:
		out << "High_Card";
		break;
	default:
		break;
	}
	return out;
}