#include "Damage_Num_Base.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_Damage_Num_Base::C_Damage_Num_Base(const D3DXVECTOR3 * Pos_3D, const D3DXMATRIX * Mat, const int * Damage_Num)
{
	Judg judg;

	M_Vec = (*Pos_3D) - judg.SetPosM(Mat);

	M_Damage_Num = *Damage_Num;

	M_Draw_Flg = false;

	M_Count = 40;

	M_ScalSize = 0.3f;

	M_TEX.Width = 1010;
	M_TEX.Height = 93;

	M_TEX.Tex = textureManager.GetTexture("Char_Num_1.png", M_TEX.Width, M_TEX.Height, NULL);
}

bool C_Damage_Num_Base::Update(void)
{
	if (M_Draw_Flg != true)return true;

	M_Count--;

	if (M_Count > 0)return true;

	M_Count = 0;

	return false;
}

void C_Damage_Num_Base::Move(void)
{
}

void C_Damage_Num_Base::Draw_2D(void)
{
	if (M_Draw_Flg != true)return;

	Move();

	if ((M_Pos_2D.z < 0.0f) || (M_Pos_2D.z > 1.0f))return;

	int L_w = M_TEX.Width / 10, L_h = M_TEX.Height;

	char cNum[64];
	sprintf_s(cNum, sizeof(cNum), "%d", M_Damage_Num);

	int Num;
	for (Num = 0; cNum[Num] != '\0'; Num++);

	if (Num < 1)return;

	D3DXMATRIX Mat, TransMat;

	Judg judg;

	//1桁
	if (Num >1) {
		int Type_Num = Num % 2;
		int Judg_Num = Num / 2;

		D3DXVECTOR2 TransPos = D3DXVECTOR2((float)L_w*M_ScalSize*0.84f, 0.0f),
			Pos;
		Pos = TransPos;
		for (int i = 0; i < Judg_Num; i++) {
			if (i == 0) {
				if ((i == 0) && (Type_Num < 1))Pos /= 2.0f;
				judg.Set_Vec3_Vec2(&M_Pos_2D, &Pos);
			}
			else {
				judg.Set_Vec3_Vec2(&M_Pos_2D, &TransPos);
			}
		}
		Pos = TransPos * -1.0f;
		D3DXMatrixTranslation(&TransMat, Pos.x, Pos.y, NULL);
	}

	Mat = judg.Set_2DMat(&M_Pos_2D);
	
	//表示
	RECT rcNum[] = {
		{L_w * 0,0,L_w + L_w * 0,L_h },
		{L_w * 1,0,L_w + L_w * 1,L_h },
		{L_w * 2,0,L_w + L_w * 2,L_h },
		{L_w * 3,0,L_w + L_w * 3,L_h },
		{L_w * 4,0,L_w + L_w * 4,L_h },
		{L_w * 5,0,L_w + L_w * 5,L_h },
		{L_w * 6,0,L_w + L_w * 6,L_h },
		{L_w * 7,0,L_w + L_w * 7,L_h },
		{L_w * 8,0,L_w + L_w * 8,L_h },
		{L_w * 9,0,L_w + L_w * 9,L_h },
	};

	int Count_for = 0;
	D3DXMATRIX TmpMat;
	for (Num -= 1; Num >= 0; Num--) {
		if (Count_for == 0) {
			Count_for = 1;
		}
		else {
			Mat *= TransMat;
		}
		TmpMat = judg.getScalingMat(&judg.Get_Size2D(&M_ScalSize))*Mat;
		lpSprite->SetTransform(&TmpMat);

		lpSprite->Draw(M_TEX.Tex, &rcNum[cNum[Num] - '0'], &D3DXVECTOR3((float)L_w / 2.0f, (float)L_h / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

D3DXVECTOR3 C_Damage_Num_Base::Get_Pos_3D(const D3DXMATRIX * Mat)
{
	Judg judg;
	D3DXVECTOR3 Pos = judg.SetPosM(Mat) + M_Vec;
	return Pos;
}

void C_Damage_Num_Base::Set_Pos_2D(const D3DXVECTOR3 * Pos_2D)
{
	if (M_Draw_Flg != true)M_Draw_Flg = true;

	M_Pos_2D = *Pos_2D;
}
