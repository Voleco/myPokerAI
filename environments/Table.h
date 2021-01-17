
#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <utility>
#include"Deck.h"
#include"Action.h"


using std::string;
using std::vector;

typedef std::pair<unsigned int, Action> Player_Action;

class TableState
{
public:
	TableState() {}
private:
	//number of players on the table
	int num_players;
	//a circular queue that stores all the players' ID on table
	vector<unsigned int> playerIDs;

	//chip for each player
	vector<int> chipCounts;

	//current chips in pot 
	int chipsInPot;

	//current betting amount
	int currentBet;

	//index of the small blind player of current hand
	//e.g. SBIndex is 2, then playerIDs[2] is SB, playerIDs[3] is BB, ... playerIDs[1] is bottom
	unsigned int SBIndex;

	//the history of previous actions, including bet, fold, raise operations, associated with playerID
	vector<Player_Action> playerActions;
};


class Table
{
public:
	Table() {}
	void GetActions(TableState& state, unsigned int playerID, vector<Action>& actions);
	void ApplyAction(TableState& state, unsigned int playerID, Action action);
};


#endif // !TABLE_H


