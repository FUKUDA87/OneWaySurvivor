#pragma once
#include"../../No1/Speed/SpeedUp.h"


class C_Enemy101_Speed_1 :public SpeedUp1{
public:
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
};