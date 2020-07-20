#pragma once
#include"../../Car/Parts/Car_Parts_Joint.h"

class C_Stand_No101 :public C_Car_Parts_Joint
{
public:
	C_Stand_No101(const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base * Move);
private:
	void Init_Joint_Data(const bool *Joint_Reverse_Flg);
};