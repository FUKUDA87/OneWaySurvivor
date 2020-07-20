#include "Game_End_Now.h"
#include"Game_Clear.h"
#include"GameOver.h"

C_Game_End_Base * C_Game_End_Now::Change(const int * Mode)
{
	switch (*Mode)
	{
	case 1:
		return new C_Game_Clear();
		break;
	case 2:
		return new C_Game_Over();
		break;
	default:
		break;
	}

	return nullptr;
}
