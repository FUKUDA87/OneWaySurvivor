#include "Bullet_No2.h"
#include"../../Draw/DrawBase2/DrawPolMat/PolMat_Bullet_No1.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Bullet_No2::C_Bullet_No2(const D3DXMATRIX * Mat) :C_Bullet_Base(Mat)
{
	Init_No2();
}

C_Bullet_No2::C_Bullet_No2(const D3DXMATRIX * Mat, const S_RayHitJudgData * RayData) :C_Bullet_Base(Mat, RayData)
{
	Init_No2();
}

void C_Bullet_No2::Init_No2(void)
{
	M_S_Bullet.Damage = 2;
	M_S_Bullet.Speed = 1.1f;

	M_Draw.push_back(new C_PolMat_Bullet_No1("Bullet1-1-1.png"
		, &Get_Tex_Pos(100, 100), &Get_Init_S_PolMat_INIT(&M_Base.Mat, 1, 4, 0.1f)));
	M_Draw.push_back(new C_Draw_Mesh_Base("Missile.x",&D3DXVECTOR3(0.1f,0.1f,0.1f)));
}
