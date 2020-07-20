#include "Bullet_No1.h"
#include"../../Draw/DrawBase2/DrawPolMat/PolMat_Bullet_No1.h"

C_Bullet_No1::C_Bullet_No1(const D3DXMATRIX * Mat):C_Bullet_Base(Mat)
{
	Init_No1();
}

C_Bullet_No1::C_Bullet_No1(const D3DXMATRIX * Mat, const S_RayHitJudgData * RayData):C_Bullet_Base(Mat,RayData)
{
	Init_No1();
}

void C_Bullet_No1::Init_No1(void)
{
	M_S_Bullet.Damage = 1;
	M_S_Bullet.Speed = 1.1f;

	M_Draw.push_back(new C_PolMat_Bullet_No1("Bullet1-1-1.png"
		, &Get_Tex_Pos(100, 100), &Get_Init_S_PolMat_INIT(&M_Base.Mat, 1, 4, 0.1f)));
}
