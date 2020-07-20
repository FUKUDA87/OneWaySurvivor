#pragma once
#include"GunMove.h"

class C_GunBulletA :public C_GunMove {
public:
	C_GunBulletA();
	C_GunMove *Action(GUNAI* GunAi);
private:
	bool InitFlg;
};