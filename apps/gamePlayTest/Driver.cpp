
#include <iostream>
#include <vector>
#include <time.h>
#include <cstring>

#include "../../environments/Table.h"
#include"../../environments/GameEngine.h"
#include"../../environments/Player.h"
#include"../../environments/RandomPlayer.h"


using std::cout;

int main(int argc,char** argv)
{
	/*
	if (argc > 1 && strcmp(argv[1], "-buildPDB") == 0)
	{


	}

	else if (argc > 1 && strcmp(argv[1], "-run") == 0)
	{
	
	}

	else
	{
		std::cout << "Usage: " << argv[0] << " -hehe\n";
	}
	*/
	GameEngine eng;
	eng.SetTableSize(8);
	eng.ClearTable();

	RandomPlayer player1(101);
	RandomPlayer player2(102);
	RandomPlayer player3(103);

	player1.AddChips(1000);
	player2.AddChips(800);
	player3.AddChips(900);
	eng.AddPlayerToPos(&player1, 0);
	eng.AddPlayerToPos(&player2, 2);
	eng.AddPlayerToPos(&player3, 4);


	eng.SetBlindLevel(2, 4, 0, 1);
	eng.SetNextSmallBlindPos(0);

	cout<<"1\n";

	for (unsigned int i = 0; i < eng.tableCapacity; i++)
	{
		if(eng.seatActive[i])
		//cout<<*((RandomPlayer*)(eng.playerPtrs[i]));
		eng.playerPtrs[i]->PrintPlayerInfo();
	}	

	for(int i=0;i<1;i++)
	{
		eng.InitializeOneGame();
		cout<<"2\n";
		eng.DealPlayerCards();
		cout<<"3\n";
		for (unsigned int i = 0; i < eng.tableCapacity; i++)
		{
			if(eng.activePlayersInPot[i])
				//cout<<*((RandomPlayer*)(eng.playerPtrs[i]));
				eng.playerPtrs[i]->PrintPlayerInfo();
		}
	}

	

	return 0;
}
