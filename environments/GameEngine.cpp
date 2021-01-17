
#include"GameEngine.h"

void GameEngine::SetBlindLevel(int sb, int bb, int num_st, int at)
{
	num_st_table = num_st;
	blinds.resize(0);
	blinds.push_back(sb);
	blinds.push_back(bb);
	int st = bb * 2;
	while (blinds.size() < tableCapacity)
	{
		blinds.push_back(st);
		st = st * 2;
	}
	ante = at;
}

void GameEngine::ClearTable()
{
	playerPtrs.resize(0);
	for (unsigned int i = 0; i < tableCapacity; i++)
		playerPtrs.push_back(NULL);
}

bool GameEngine::AddPlayerToPos(Player<GameEngine,Action>* p, unsigned int pos)
{
	if (pos > tableCapacity)
		return false;
	if (playerPtrs[pos] != NULL)
		return false;
	playerPtrs[pos] = p;
	return true;
}

void GameEngine::InitializeOneGame()
{
	int pot = 0;
	//collect ante and put them into pot
	/*
	for (unsigned int i = 0; i < tableCapacity; i++)
	{
		if (playerPtrs[i])
		{
			playerPtrs[i]->addChips(-ante);
			pot += ante;
		}
	}
	*/
	for (unsigned int i = 0; i < activeSeats.size(); i++)
	{
		playerPtrs[activeSeats[i]]->AddChips(-ante);
		pot += ante;
	}
	

}

void GameEngine::GetLegalActions(unsigned int playerID, vector<Action>& acts)
{
	
}