#pragma once
#include"../../Enemy/Data/Base&Manager/EnemySpeed.h"

class c_SpeedDeadStop :public C_Speed_Update {
public:
	c_SpeedDeadStop();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
private:
	bool InitFlg;  // ‰Šú‰»ƒtƒ‰ƒO
};