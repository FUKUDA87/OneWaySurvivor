#include "Draw_Ball_A.h"
#include"../../GameSource/Judgment.h"

C_Draw_Ball_A::C_Draw_Ball_A(const float Dis)
{
	M_Dis = Dis;
	Draw_JudgFlg = Co_Draw_Ball;

	Count = 10;
}

C_Draw_Ball_A::~C_Draw_Ball_A()
{
	Delete_All_Ball();
}

void C_Draw_Ball_A::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Count--;
	if(Count==0)M_Ball.push_back(new c_Ball3D(Get_Dis()));
	if (Count < 0)Count = 0;

	if (M_Ball.size() < 1)return;

	for (auto && b : M_Ball) {
		Judg judg;
		b->SetPos(&judg.SetPosM(&Get_DrawMat()));
		b->Draw();
	}
}

LPD3DXMESH C_Draw_Ball_A::Get_Mesh(void)
{
	return LPD3DXMESH();
}

D3DXVECTOR3 C_Draw_Ball_A::Get_Pol_Pos(const int * PosNo)
{
	return D3DXVECTOR3();
}

float C_Draw_Ball_A::Get_Dis(void)
{
	float f = (Get_ScalPos().x + Get_ScalPos().y + Get_ScalPos().z) / 3.0f;
	if (f < 0.0f)f *= -1.0f;

	f = M_Dis * f;
	return f;
}

void C_Draw_Ball_A::Delete_All_Ball(void)
{
	if (M_Ball.size() < 1)return;

	for (unsigned int b = 0; b < M_Ball.size(); b++) {
		delete M_Ball[b];
		M_Ball.erase(M_Ball.begin() + b);
		b--;
	}
}
