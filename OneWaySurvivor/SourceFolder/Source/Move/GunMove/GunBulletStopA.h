#pragma once
#include"GunMove.h"

class C_GunBulletStopA :public C_GunMove {
public:
	C_GunBulletStopA();
	C_GunMove *Action(GUNAI* GunAi);
private:
	bool InitFlg;
};