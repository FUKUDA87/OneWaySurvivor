#pragma once
#include"../../Base&Manager/EnemySpeed.h"

class SpeedUp1:public C_Speed_Update {
public:
	SpeedUp1();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
protected:
	//•Ï‰»—Ê
	int SpeedUpNum;
};

class SpeedUp2 :public SpeedUp1 {
public:
	SpeedUp2();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
private:
};