#pragma once
#include"../../No1/Speed/SpeedDown.h"


class C_Enemy101_Speed_3 :public SpeedDown1 {
public:
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
};