#pragma once
#include"../../Car/Parts/Car_Parts_Joint.h"

class C_Door_No1 :public C_Car_Parts_Joint
{
public:
	C_Door_No1(const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base * Move);
};