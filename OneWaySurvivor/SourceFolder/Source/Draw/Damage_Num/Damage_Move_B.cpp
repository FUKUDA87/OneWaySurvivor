#include "Damage_Move_B.h"

C_Damage_Move_B::C_Damage_Move_B(const D3DXVECTOR3 * Pos_3D, const D3DXMATRIX * Mat, const int * Damage_Num):C_Damage_Num_Base(Pos_3D, Mat, Damage_Num)
{
	Pos = D3DXVECTOR2(0.0f, 0.0f);
	UpY = -1.0f;
	M_Count = 30;
}

void C_Damage_Move_B::Move(void)
{
	Pos.y += UpY;
	M_Pos_2D.x += Pos.x;
	M_Pos_2D.y += Pos.y;
}
