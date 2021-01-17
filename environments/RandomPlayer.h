
#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include"Card.h"
#include"Table.h"
#include"Player.h"
#include"GameEngine.h"

using std::string;
using std::vector;



class RandomPlayer:public Player<GameEngine,Action>
{
public:
	RandomPlayer() {}
	RandomPlayer(unsigned int id) { playerID = id; }
	//Player(int chipcnt) { chipCount = chipcnt; }
	virtual void InitializePlayer() { chipCount = 0; }
	virtual void AddChips(int amount) { chipCount += amount; }
	virtual void InformLegalActions(GameEngine& eng) ;
	virtual void TakeAction(GameEngine& eng, Action a) ;
private:

};

void RandomPlayer::InformLegalActions(GameEngine& eng)
{
	eng.GetLegalActions(playerID, acts);
}

void RandomPlayer::TakeAction(GameEngine& eng, Action a)
{
	
}



#endif // !RANDOMPLAYER_H


