#pragma once
#include"../../No1/Speed/SpeedUp.h"

class C_Enemy101_Speed_2 :public SpeedUp1 {
public:
	C_Enemy101_Speed_2();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
protected:

	//ターゲットからの地面の差
	int M_Ground_Number;
};