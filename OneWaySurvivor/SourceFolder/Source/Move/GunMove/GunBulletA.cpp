#include "GunBulletA.h"
#include"GunBulletStopA.h"

C_GunBulletA::C_GunBulletA()
{
	InitFlg = true;
}

C_GunMove * C_GunBulletA::Action(GUNAI * GunAi)
{
	//Ai‚ª‹@”\‚µ‚Ä‚¢‚é‚©
	if (GunAi->AIFlg == false)return nullptr;
	if (InitFlg == true) {
		GunAi->BulletCount = 0;
		GunAi->BulletNum = 1;
		GunAi->BulletFlg = false;
		InitFlg = false;
	}
	
	if (GunAi->BulletNum <= 0)return new C_GunBulletStopA();

	if (GunAi->BulletCount > 0)GunAi->BulletCount -= 1;
	//”­ŽË
	if (GunAi->BulletCount <= 0) {
		GunAi->BulletFlg = true;
		GunAi->BulletNum -= 1;
		GunAi->BulletCount = 0;
	}

	return nullptr;
}
