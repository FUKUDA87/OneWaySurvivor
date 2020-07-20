#include "Bullet_No99.h"

C_Bullet_No99::C_Bullet_No99(const D3DXMATRIX * Mat):C_Bullet_No2(Mat)
{
	Init_99();
}

C_Bullet_No99::C_Bullet_No99(const D3DXMATRIX * Mat, const S_RayHitJudgData * RayData):C_Bullet_No2(Mat,RayData)
{
	Init_99();
}

void C_Bullet_No99::Init_99(void)
{
	M_S_Bullet.Damage = 999;
	M_S_Bullet.Speed = 2.5f;
}
