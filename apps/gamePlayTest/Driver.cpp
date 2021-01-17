
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
	eng.AddPlayerToPos(&player1, 0);
	eng.AddPlayerToPos(&player2, 2);
	eng.AddPlayerToPos(&player3, 4);


	eng.SetBlindLevel(1, 2, 0, 0);
	eng.SetNextSmallBlindPos(0);

	eng.InitializeOneGame();
	

	return 0;
}
