
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <utility>
#include"Deck.h"
#include"Action.h"
#include"Table.h"
#include"Player.h"

using std::string;
using std::vector;

class GameEngine
{
public:
	GameEngine() {}
	void SetTableSize(unsigned int size) { tableCapacity = size; }

	//clear all the players on table
	void ClearTable();
	void SetNextSmallBlindPos(unsigned int pos) { sbPos = pos; }

	//num_st means default number of player placing straddle in this table
	//for a 2/4(1) game, call SetBlindLevel(2,4,0,1)
	//for a 3/6/12(3) game, call SetBlindLevel(3,6,1,3)
	void SetBlindLevel(int sb, int bb, int num_st =0, int at=0);
	
	bool AddPlayerToPos(Player<GameEngine,Action>* p, unsigned int pos);

	void InitializeOneGame();

	void GetLegalActions(unsigned int playerID, vector<Action>& acts);

private:
	Deck deck;
	Table table;
	TableState currentState;
	
	unsigned int tableCapacity;

	//ante of a game
	int ante;

	//a vector storing the blind info. e.g. for a 6-player 2/4(1) level game, blinds = {2,4,8,16,32,64}
	vector<int> blinds;

	//a vector storing all the players on table. the size of vector is always the size of the table; if a seat is empty,
	//the pointer is NULL. e.g. A 4-player table, 2 players on seat, the vector may look like {player1 ,NULL, NULL, player2}
	vector<Player<GameEngine,Action>*> playerPtrs;

	//sbPos in the range of (0,tableCapacity), representing the next player to put small blind.
	unsigned int sbPos;

	//a vector(should be a list) storing the index of active players in playerPtrs.
	vector<unsigned int> activeSeats;

	// num_st_table is the number of players doing straddle for the table. 1/2 level game, num_st_table == 0, 3/6/12, num_st_table == 1
	// for each game, players can do straddle as they want. a 1/2, UTG play can do st, then num_st_game = 1
	int num_st_table;
	int num_st_game;
};


#endif // !GAMEENGINE_H


