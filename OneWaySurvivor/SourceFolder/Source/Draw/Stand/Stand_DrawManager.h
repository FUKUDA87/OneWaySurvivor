#pragma once
#include"Stand_No1.h"

class C_Stand_DrawManager {
public:
	C_Car_Parts_Joint* Get_Draw(const int *StandNo, const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base * Move);
	C_Car_Parts_Joint* Get_Draw_Stop(const int *StandNo, const S_CAR_PARTS_DATA *Data);
};