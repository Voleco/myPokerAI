#include"Evaluator.h"


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
Royal_Flush         9         0x9FFF
Straight_Flush      8         0x8FFF
Four_of_a_Kind      7         0x7FFF
Full_Houses         6         0x6FFF
Flush               5         0x5FFF
Straight            4         0x4FFF
Three_of_a_Kind     3         0x3FFF
Two_Pair            2         0x2FFF
One_Pair            1         0x1FFF
High_Card           0         0x0FFF
*/

void HandEvaluator::BuildDATFile()
{
	RankingCombination rc;

	const int TOTAL = 2598960;
	uint16_t* handValueLookupTable = new uint16_t[TOTAL];

	int* cards_int = new int[5];
	Card* cards = new Card[5];

	

	for(int x=0;x<TOTAL;x++)
	{
		if (x%25000==0)
		{
			cout<<"current process: x= " << x<<"\n";
		}

		
		uint64_t hash = (uint64_t)(x);
		uint16_t handVal = 0;
		rc.Unrank(x,cards_int,5,52);
		//now we get a hand of 5 cards, sorting in accending order
		

		for(int i=0;i<5;i++)
			cards[i] = Int_to_card(cards_int[i]+1);
		
		vector<int> ranks;
		vector<int> suits;
		vector<int> distinct_ranks;
		for(int i=0;i<5;i++)
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
		
		
		if(distinct_ranks.size()==2)//Full house, Four of a kind
		{
			//main part and kicker
			int m, k;
			if (ranks[0]!=ranks[1])// kmmmm, four of a kind
			{				
				m = ranks[1]-2;
				k = ranks[0]-2;
				handVal = handVal | 0x7000;
				handVal += m*12 + k;
			}
			else if(ranks[1]!=ranks[2])//kkmmm, full house
			{
				m = ranks[2]-2;
				k = ranks[1]-2;
				handVal = handVal | 0x6000;
				handVal += m*12 + k;
			}
			else if(ranks[2]!=ranks[3])//mmmkk, full house
			{
				m = ranks[2]-2;
				k = ranks[3]-2;
				handVal = handVal | 0x6000;
				handVal += m*12 + k-1;
			}
			else//mmmmk, four of a kind
			{
				m = ranks[3]-2;
				k = ranks[4]-2;
				handVal = handVal | 0x7000;
				handVal += m*12 + k-1;
			}
			
		}
		else if (distinct_ranks.size()==3)//Two pairs, Three of a Kind
		{
			int a,b,c;
			if(ranks[0]!=ranks[1])
			{
				if (ranks[1]!=ranks[2])//abccc, Three of a Kind
				{
					a = ranks[0]-2;
					b = ranks[1]-2;
					c = ranks[4]-2;
					handVal = handVal | 0x3000;
					handVal += c*12*11/2 + a*11 + b-1;
				}
				else if(ranks[2]==ranks[3])//abbbc, Three of a Kind
				{
					a = ranks[0]-2;
					b = ranks[1]-2;
					c = ranks[4]-2;
					handVal = handVal | 0x3000;
					handVal += b*12*11/2 + a*11 + c-2;
				}
				else//abbcc,Two pairs
				{
					a = ranks[0]-2;
					b = ranks[1]-2;
					c = ranks[4]-2;
					handVal = handVal | 0x2000;
					handVal += c*12*11/2 + (b-1)*11 + a;
				}
			}
			else if(ranks[1]!=ranks[2])
			{
				if(ranks[2]!=ranks[3])//aabcc,Two pairs
				{
					a = ranks[0]-2;
					b = ranks[2]-2;
					c = ranks[4]-2;
					handVal = handVal | 0x2000;
					handVal += c*12*11/2 + a*11 + b-1;
				}
				else//aabbc,Two pairs
				{
					a = ranks[0]-2;
					b = ranks[2]-2;
					c = ranks[4]-2;
					handVal = handVal | 0x2000;
					handVal += b*12*11/2 + a*11+c-2;
				}
			}
			else //aaabc, Three of a Kind
			{
				a = ranks[0]-2;
				b = ranks[3]-2;
				c = ranks[4]-2;
				handVal = handVal | 0x3000;
				handVal += a*12*11/2 + (b-1)*11+(c-2);
			}

		}
		else if (distinct_ranks.size()==4)//One pair
		{
			int nums[4];
			int index = 0;
			int offset = 0;
			for (int j=0;j<5;j++)
			{
				if (ranks[j]==ranks[j+1])
				{
					index = j;
					offset = 1;
					continue;
				}
				nums[j-offset] = ranks[j] - 2;
			}
			handVal = handVal | 0x1000;
			handVal += nums[index]*12*11*10/6;
			int terms[3] = {55,10,1};
			for (int j=0;j<4;j++)
			{
				if (j<index)
					handVal += (nums[j]-j)*terms[j];
				if(j>index)
					handVal += (nums[j]-j)*terms[j-1];
			}

		}
		else if (distinct_ranks.size()==5)//High card, Flush, Straight, SF, RF
		{
			bool is_flush = false;
			bool is_straight = false;
			bool is_SF = false;
			bool is_RF = false;

			//determine whether it is straight of A,2,3,4,5
			bool straight_A = false;
			if (suits[0]==suits[1]&& suits[0]==suits[2]&& suits[0]==suits[3]&&suits[0]==suits[4])
				is_flush = true;

			if (ranks[0]==2 && ranks[1]==3  && ranks[2]==4 && ranks[3]==5 && ranks[4]==14)
				straight_A = true;
			if (ranks[0]==ranks[1]-1 && ranks[0]==ranks[2]-2 && ranks[0]==ranks[3]-3 && ranks[0]==ranks[4]-4 || straight_A)
				is_straight = true;

			if (is_straight && is_flush)
				is_SF = true;

			uint64_t value = 0;

/*
6 High            4  choose 4       1
7 High            5  choose 4       5
...
A High           12  choose 4      495
*/
			//lets say this hand is Ahigh. we need to count the total number of 6-high, 7-high, ... K-high

			for (int j=4;j>=0;j--)
			{
				for (int k=j;k<ranks[j]-2;k++)
				{
					value += rc.NChooseK(k,j);
				}
			}

			if (is_flush==true && is_straight==true )
			{
				if (value == 1286) //RF
				{
					handVal = 0x9000;
					handVal += value;
				}
				else//SF
				{
					handVal = 0x8000;
					if (straight_A)
						handVal += 5;
					else
						handVal += ranks[4];
				}
			}
			else if(is_flush==true && is_straight==false )//Flush
			{
					handVal = 0x5000;
					handVal += value;
			}
			else if(is_flush==false && is_straight==true )//Straight
			{
					handVal = 0x4000;
					if (straight_A)
						handVal += 5;
					else
						handVal += ranks[4];
			}
			else//High Card
			{
					handVal = 0x0000;
					handVal += value;
			}			

		}

/*
		cout<<"cards: ";
		for (int i =0;i<5;i++)
			cout<<cards[i];
		cout<<"\n";
		cout<<"handVal: "<<std::hex<<handVal<<"\n";
*/
		handValueLookupTable[x] = handVal;
	

	}


//validation


map<uint64_t,int> handValMap;


for (int i=0;i<TOTAL;i++)
{
	if(handValMap.find( handValueLookupTable[i])!= handValMap.end())
		handValMap[handValueLookupTable[i]]++;
	else
		handValMap[handValueLookupTable[i]] = 1;
}

cout<<"handValMap size: "<<handValMap.size()<<"\n";


vector<int> counts;
for (int i=0;i<10;i++)
 { counts.push_back(0);}
for (auto it=handValMap.begin();it!=handValMap.end();it++)
{
	uint16_t handType = it->first & 0xF000;
	handType = handType>>12;
	if(handType == 8)
		cout<<"sf value: "<<std::hex<<it->first<<"\n";
	counts[handType]++;

}
for (int i=0;i<10;i++)
{
	cout<<"type "<<i<<" : "<<counts[i]<<"\n";
}

}

bool HandEvaluator::LoadDATFlie()
{
	return false;
}

uint64_t HandEvaluator::HandValue(Card c1, Card c2, Card c3, Card c4, Card c5)
{
	return 0;
}

