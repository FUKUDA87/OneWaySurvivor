#pragma once
#include"Car_Tire_No1.h"

class C_Tire_DrawManager {
public:
	//表示渡し
	C_Car_Parts_Joint* Get_Draw(const int *TireNo, const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base *Move);

	//無動セット
	C_Car_Parts_Joint* Get_Draw_Stop(const int *TireNo, const S_CAR_PARTS_DATA *Data);

	//無動セット
	C_Car_Parts_Joint* Get_Draw_Tire(const int *TireNo, const S_CAR_PARTS_DATA *Data);
private:
	
};