
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include"Card.h"
#include"Table.h"

using std::string;
using std::vector;
using std::cout;



template <class engine, class action>
class Player
{
public:
	Player() {chipCount = 0;}
	Player(unsigned int id) { playerID = id; chipCount = 0; }
	//Player(int chipcnt) { chipCount = chipcnt; }
	virtual void InitializePlayer() ;
	virtual void AddChips(int amount) ;
	int GetChipsCount() {return chipCount;}
	virtual void GetPrivateCard(Card c) ;
	virtual void GetLegalActions(engine& eng, vector<action>& acts) ;
	virtual void InformLegalActions(engine& eng) ;
	virtual void TakeAction(engine& eng, action a) ;
	virtual void PrintPlayerInfo();
protected:
	vector<Card> playerCards;
	int chipCount;
	unsigned int playerID;
	vector<action> acts;
};

template <class engine, class action>
void Player<engine,action>::InitializePlayer()
{

}

template <class engine, class action>
void Player<engine,action>::AddChips(int amount)
{
	chipCount += amount;
}

template <class engine, class action>
void Player<engine,action>::GetPrivateCard(Card c)
{
	playerCards.push_back(c);
}

template <class engine, class action>
void Player<engine,action>::GetLegalActions(engine& eng, vector<action>& acts)
{
}

template <class engine, class action>
void Player<engine,action>::InformLegalActions(engine& eng) 
{
}

template <class engine, class action>
void Player<engine,action>::TakeAction(engine& eng, action a)
{
}

template <class engine, class action>
void Player<engine,action>::PrintPlayerInfo()
{
	cout << "playerID: "<<playerID <<", chipCount: "<<chipCount<<" private cards:";
	for(unsigned int i=0;i<playerCards.size();i++)
		cout<<playerCards[i];
	cout<<" legal actions: ";
	for(unsigned int i=0;i<acts.size();i++)
		cout<<acts[i];
	cout<<"\n";
}


#endif // !PLAYER_H


