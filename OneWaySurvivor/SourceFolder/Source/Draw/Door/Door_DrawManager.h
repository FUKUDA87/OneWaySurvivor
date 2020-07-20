#pragma once
#include"Door_No1.h"

class C_Door_DrawManager {
public:
	//表示渡し
	C_Car_Parts_Joint* Get_Draw(const int *DoorNo, const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base *Move);

	//無動セット
	C_Car_Parts_Joint* Get_Draw_Stop(const int *DoorNo, const S_CAR_PARTS_DATA *Data);

	//無動セット
	C_Car_Parts_Joint* Get_Draw_Door(const int *DoorNo, const S_CAR_PARTS_DATA *Data,const float *MoveAng);
private:

};