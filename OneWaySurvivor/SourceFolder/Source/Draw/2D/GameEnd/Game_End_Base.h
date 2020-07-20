#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"

class C_Game_End_Base {
public:
	C_Game_End_Base();

	virtual C_Game_End_Base* Change(const int *Mode) = 0;

	virtual void Draw_2D(void);

	bool Get_EndFlg(void) {
		return Game_End_Flg;
	}
protected:
	bool Game_End_Flg;
private:

};