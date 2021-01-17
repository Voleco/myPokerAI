
#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include"Card.h"


using std::string;
using std::vector;

enum ActionType
{
	tFold = 0,
	tCheck = 1,
	tCall = 2,
	tRaise = 3
};

class Action
{
public:
	Action() {}
	ActionType actionTpye;
	int actionValue;
};

#endif // !ACTION_H


