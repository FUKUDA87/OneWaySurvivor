#pragma once
#include"Game_End_Base.h"

class C_Game_Over:public C_Game_End_Base {
public:
	C_Game_Over();

	C_Game_End_Base* Change(const int *Mode);

	void Draw_2D(void);

protected:
	CHARA2D gaov;
};