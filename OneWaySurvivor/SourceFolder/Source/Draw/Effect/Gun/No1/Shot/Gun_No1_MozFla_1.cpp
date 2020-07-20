#include "Gun_No1_MozFla_1.h"

C_Gun_No1_MuzFla_1::C_Gun_No1_MuzFla_1(const D3DXMATRIX * Gun_Mouth_Mat)
{
	Init_Mat(Gun_Mouth_Mat);

	Init_Load();

	Init_Pol_Set();

	AliveFlg = true;
}

void C_Gun_No1_MuzFla_1::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Draw_Pol_No2();

	AliveFlg = false;
}

bool C_Gun_No1_MuzFla_1::Update(void)
{
	return AliveFlg;
}

void C_Gun_No1_MuzFla_1::Init_Load(void)
{
	S_TEX_POS Pos;
	Pos.Width = 128;
	Pos.Height = 128;
	Texture_Load("MuzFla1T.png", &Pos);
}

void C_Gun_No1_MuzFla_1::Init_Mat(const D3DXMATRIX * Gun_Mouth_Mat)
{
	D3DXMATRIX Mat = *Gun_Mouth_Mat,RotZ;

	int Ang = rand() % 3600;
	float AngZ = (float)Ang / 10.0f;

	D3DXMatrixRotationZ(&RotZ, D3DXToRadian(AngZ));

	Mat = RotZ * Mat;

	Set_Mat(&Mat);

}

void C_Gun_No1_MuzFla_1::Init_Pol_Set(void)
{
	int A = 255;
	Pol_SetAllColor(&A);

	Pol_SetAllTex(&D3DXVECTOR2(0.0f, 0.0f), &D3DXVECTOR2(1.0f, 0.0f), &D3DXVECTOR2(1.0f, 1.0f), &D3DXVECTOR2(0.0f, 1.0f));

	D3DXVECTOR3 Pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	Pos *= 0.25f;

	Pol_SetPos(&D3DXVECTOR3(-Pos.x, Pos.y, Pos.z), &D3DXVECTOR3(Pos.x, Pos.y, Pos.z), &D3DXVECTOR3(Pos.x, -Pos.y, Pos.z), &D3DXVECTOR3(-Pos.x, -Pos.y, Pos.z));
}
