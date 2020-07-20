#pragma once
#include"Game_End_Base.h"

class C_Game_Clear :public C_Game_End_Base {
public:
	C_Game_Clear();

	C_Game_End_Base* Change(const int *Mode);

	void Draw_2D(void);

protected:

private:
	CHARA2D stcl;
};