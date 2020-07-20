#pragma once
#include"Sound_BGM_Base.h"

class C_Sound_BGM_Manager {
public:
	C_Sound_Base_2D* Get_BGM(const int *No);
	int Get_BGM_Num(void) {
		return 4;
	}

};