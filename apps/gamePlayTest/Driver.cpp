
#include <iostream>
#include <vector>
#include <time.h>
#include <cstring>

#include "../../environments/Table.h"
#include"../../environments/GameEngine.h"
#include"../../environments/Player.h"
#include"../../environments/RandomPlayer.h"
#include"../../environments/Evaluator.h"
#include"../../utils/RankingCombinations.h"

using std::cout;

void gameFlowTest();
void handEvaTest(const char* prefix, int testCnt);
void rankingTest();

int main(int argc,char** argv)
{
	if (argc > 1 && strcmp(argv[1], "-testRank") == 0)
	{
		rankingTest();
	}
	if (argc > 3 && strcmp(argv[1], "-testHand") == 0)
	{
		handEvaTest(argv[2],std::atoi(argv[3]));
	}

	else if (argc > 1 && strcmp(argv[1], "-run") == 0)
	{
		gameFlowTest();
	}

	else
	{
		std::cout << "Usage: " << argv[0] << " -hehe\n";
	}
	


	

	return 0;
}

void rankingTest()
{
	// /* card to int test*/
	// Card c1("As");
	// Card c2("7c");
	// //expected to be 52 
	// cout<<"As to int: "<<Card_to_int(c1) <<"\n"; //--- passed
	// //expected to be 21 
	// cout<<"7c to int: "<<Card_to_int(c2) <<"\n"; //--- passed
	
	// /* int to card test*/
	// //expected to be As 
	// cout<<"Card of int 52: "<<Int_to_card(52) <<"\n"; //--- passed
	// //expected to be 7c  
	// cout<<"Card of int 21: "<<Int_to_card(21) <<"\n"; //--- passed

	/*ranking function test*/
	RankingCombination rc;
	//expect to see 2598960 
	cout<<"52 choose 5: " <<rc.NChooseK(52,5)<<"\n"; //--- passed

	int* arr = new int[5];
	for(int i=0;i<5;i++)
		arr[i] = i;
	cout<<"rank of [0,1,2,3,4]: " <<rc.Rank(arr,5,52)<<"\n"; //--- passed
	for(int i=0;i<5;i++)
		arr[i] = i+47;
	cout<<"rank of [47,48,49,50,51]: " <<rc.Rank(arr,5,52)<<"\n"; //--- passed

	for(int i=0;i<5;i++)
		arr[i] = 0;
	rc.Unrank(2598959,arr,5,52);
	cout<<"result of unrank 2598959:";
	for(int i=0;i<5;i++)
		cout<<arr[i]<<",";
	cout<<"\n"; //--- passed
}
void handEvaTest(const char* prefix, int testCnt)
{
	 HandEvaluator he(prefix);
	 //he.BuildDATFile();
	 Deck dk(52);


//test code for evalute 5 cards
	//  Card c1,c2,c3,c4,c5;
	//  for (int i=0;i<testCnt;i++)
	//  {
	// 	 dk.ShuffleCards();
	// 	 c1 = dk.DealOneCard();
	// 	 c2 = dk.DealOneCard();
	// 	 c3 = dk.DealOneCard();
	// 	 c4 = dk.DealOneCard();
	// 	 c5 = dk.DealOneCard();

	// 	cout<<"current hand: "<<c1<<c2<<c3<<c4<<c5<<"\n";
	// 	uint16_t res = he.GetHandValue_5_Cards(c1,c2,c3,c4,c5);

	// 	HandTypeEnum handtype = static_cast<HandTypeEnum>((res & 0xF000)>>12);
	// 	cout<<"hand type: "<<handtype<<" ,hand value: " <<std::hex<<res<<std::oct<<"\n\n";
	//  }

//test code for evaluate 7 cards

	 Card c1,c2,c3,c4,c5,c6,c7;
	 for (int i=0;i<testCnt;i++)
	 {
		 dk.ShuffleCards();
		 c1 = dk.DealOneCard();
		 c2 = dk.DealOneCard();
		 c3 = dk.DealOneCard();
		 c4 = dk.DealOneCard();
		 c5 = dk.DealOneCard();
		 c6 = dk.DealOneCard();
		 c7 = dk.DealOneCard();

		cout<<"current cards: "<<c1 <<" "<<c2 <<" "<<c3 <<" "<<c4 <<" "<<c5 <<" "<<c6 <<" "<<c7<<"\n";
		uint16_t res = he.GetHandValue_7_Cards(c1,c2,c3,c4,c5,c6,c7);

		HandTypeEnum handtype = static_cast<HandTypeEnum>((res & 0xF000)>>12);
		cout<<"hand type: "<<handtype<<" ,hand value: " <<std::hex<<res<<std::oct<<"\n\n";
	 }
	 
}

void gameFlowTest()
{
	GameEngine eng;
	eng.SetTableSize(8);
	eng.ClearTable();

	/*
	RandomPlayer player1(101);
	RandomPlayer player2(102);
	RandomPlayer player3(103);

	player1.AddChips(1000);
	player2.AddChips(800);
	player3.AddChips(900);
	eng.AddPlayerToPos(&player1, 0);
	eng.AddPlayerToPos(&player2, 2);
	eng.AddPlayerToPos(&player3, 4);	
	*/
	for (int i=0;i<8;i++)
	{
		RandomPlayer* p = new RandomPlayer((unsigned int)(100+i));
		p->AddChips(900);
		eng.AddPlayerToPos(p,i);
	}

	eng.SetBlindLevel(2, 4, 0, 1);
	eng.SetNextSmallBlindPos(0);

	//cout<<"1\n";

	// for (unsigned int i = 0; i < eng.tableCapacity; i++)
	// {
	// 	if(eng.seatActive[i])
	// 	//cout<<*((RandomPlayer*)(eng.playerPtrs[i]));
	// 	eng.playerPtrs[i]->PrintPlayerInfo();
	// }	

	for(int i=0;i<1;i++)
	{
		eng.InitializeOneGame();
		//cout<<"2\n";
		eng.DealPlayerCards();
		//cout<<"3\n";
		for (unsigned int i = 0; i < eng.tableCapacity; i++)
		{
			if(eng.activePlayersInPot[i])
				//cout<<*((RandomPlayer*)(eng.playerPtrs[i]));
				eng.playerPtrs[i]->PrintPlayerInfo();
		}
	}
}