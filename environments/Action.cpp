
#include"Action.h"


std::ostream& operator <<(std::ostream& out, const Action& a)
{
	switch (a.actionTpye)
	{
	case tFold:
		out<<"fold";
		break;
	case tCheck:
		out<<"check";
		break;
	case tCall:
		out<<"call "<<a.actionValue;
		break;
	case tRaise:
		out<<"raise to" <<a.actionValue;
		break;
	default:
		break;
	}
	return out;
}


