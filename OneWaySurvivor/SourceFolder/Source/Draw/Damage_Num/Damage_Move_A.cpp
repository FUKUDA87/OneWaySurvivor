#include "Damage_Move_A.h"

C_Damage_Move_A::C_Damage_Move_A(const D3DXVECTOR3 * Pos_3D, const D3DXMATRIX * Mat, const int * Damage_Num):C_Damage_Num_Base(Pos_3D,Mat,Damage_Num)
{
	UpY = 0.15f;
	UpVec.x = (float)(rand() % 7 + 5) / 10.0f;
	if (rand() % 2 > 0)UpVec.x *= -1.0f;
	UpVec.y = -3.0f;
	Pos = D3DXVECTOR2(0.0f, 0.0f);
}

void C_Damage_Move_A::Move(void)
{
	UpVec.y += UpY;
	Pos += UpVec;
	M_Pos_2D.x += Pos.x;
	M_Pos_2D.y += Pos.y;
}
