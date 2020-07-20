#pragma once
#include"../../Enemy/Data/Base&Manager/EnemySpeed.h"

class Speed_Dead_A :public C_Speed_Update {
public:
	Speed_Dead_A();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
protected:

private:
	int Count_Now, Count_Start;
	bool InitFlg;
};