#pragma once
#include"../../Base&Manager/EnemySpeed.h"

class SpeedDown1 :public C_Speed_Update {
public:
	SpeedDown1();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
protected:
	//•Ï‰»—Ê
	int SpeedDownNum;
};

class SpeedDown2 :public SpeedDown1 {
public:
	SpeedDown2();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
private:
};