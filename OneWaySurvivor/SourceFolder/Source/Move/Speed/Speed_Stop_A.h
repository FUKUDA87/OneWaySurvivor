#pragma once
#include"../../Enemy/Data/Base&Manager/EnemySpeed.h"

class C_Speed_Stop_A :public C_Speed_Update {
public:
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
};