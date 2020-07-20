#include "GunBase.h"
#include"../../../../GameSource/Const.h"
#include"../../../../GameSource/Judgment.h"

C_GunBase::C_GunBase()
{
	M_S_GunData.BulletFlg = true;
	M_S_GunData.Ray_Hit_Flg = false;
	M_S_GunData.Ray_Judg_Flg = false;
	M_S_GunData.LaserDrawFlg = false;
	M_S_GunData.RateFlg = false;

	D3DXMatrixRotationX(&M_S_GunData.NowRot.RotXMat, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&M_S_GunData.NowRot.RotYMat, D3DXToRadian(0.0f));

	M_S_GunData.DrawBase.ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Init_Departure_Num();
}

C_GunBase::~C_GunBase()
{
	Delete_GunMove();

	if (M_GunParts.size() > 0)
	{
		for (unsigned int g = 0; g < M_GunParts.size(); g++) {
			delete M_GunParts[g];
			M_GunParts.erase(M_GunParts.begin() + g);
			g--;
		}
	}

	if (M_C_Trigger != nullptr)delete M_C_Trigger;

	if (M_Category_Data.size() > 0)
	{
		for (unsigned int c = 0; c < M_Category_Data.size(); c++) {
			delete M_Category_Data[c];
			M_Category_Data.erase(M_Category_Data.begin() + c);
			c--;
		}
	}
}

bool C_GunBase::Update(S_GUN_UPDATE_DATA* s_Update)
{
	//if (Dead() != false)return false;

	// 銃の動きの更新
	if (M_GunMove != nullptr)
	{
		Judg_Rate();

		C_GunMoveBase_A *L_GunMove;
		L_GunMove = M_GunMove->Update(&M_S_GunData, s_Update, &CharaBase);
		if (L_GunMove != nullptr) {
			Delete_GunMove();
			M_GunMove = L_GunMove;
		}
	}

	// 銃のパーツの更新
	if (M_GunParts.size() > 0)
	{
		for (auto && g : M_GunParts) g->Set_Mat(&M_S_GunData.DrawBase.Mat);
	}

	// カテゴリーの更新
	if (M_Category_Data.size() > 0)
	{
		for (auto && c : M_Category_Data) c->Update();
	}

	return true;
}

void C_GunBase::Draw_Gun(const D3DXVECTOR3 * CameraPos)
{
	if (Dead() != false)return;

	Draw_GunParts(CameraPos);
}

void C_GunBase::Draw(const D3DXVECTOR3 * CameraPos)
{
	Draw_Gun(CameraPos);
}

void C_GunBase::New_GunMove(C_GunMoveBase_A * s_GunMove)
{
	Delete_GunMove();

	M_GunMove = s_GunMove;
}

int C_GunBase::Get_GunMouth_Num(void)
{
	if (M_GunParts.size() < 1)return 0;

	int i = 0;
	for (auto && g : M_GunParts) {
		if (g->Get_M_Data().BulletFlg == true)i++;
	}

	return i;
}

D3DXMATRIX C_GunBase::Get_GunMouth_Mat(const unsigned int * MouthNo)
{
	D3DXMATRIX Mat= M_S_GunData.DrawBase.Mat;

	if (M_GunParts.size() < 1)return Mat;

	for (auto && g : M_GunParts) {
		if (*MouthNo == g->Get_M_Data().CategoryNo) {
			if (g->Get_M_Data().BulletFlg == true) {
				Judg judg;
				Mat = g->Get_Parts_TransMat() *Mat;
				Mat = judg.getTransMat(&g->Get_Gun_Mouth_Pos()) * Mat;
			}
		}
	}

	return Mat;
}

bool C_GunBase::Update_Trigger(const bool * TriggerFlg)
{
	if (M_C_Trigger == nullptr)return false;

	M_C_Trigger->Trigger(M_Category_Data, TriggerFlg);

	return true;
}

bool C_GunBase::Gun_Mouth_Change(void)
{
	if (M_C_Trigger == nullptr)return false;

	M_C_Trigger->Gun_Mouth_Change();

	return true;
}

void C_GunBase::Init_Departure_Num(void)
{
	M_S_GunData.Departure_Num = 0;
}

void C_GunBase::Set_ScalPos(const D3DXVECTOR3 * s_ScalPos)
{
	M_S_GunData.DrawBase.ScalPos = *s_ScalPos;

	if (M_GunParts.size() < 1)return;

	for (auto&& g : M_GunParts) {
		g->Set_ScalPos_Body(&M_S_GunData.DrawBase.ScalPos);
	}

}

int C_GunBase::Get_Draw_Parts_Draw_JudgFlg(const unsigned int * PartsNo)
{
	if (M_GunParts.size() < 1)return 0;

	if ((*PartsNo < 0) || (*PartsNo >= M_GunParts.size()))return 0;

	if (Dead() == true)return 0;

	return M_GunParts[*PartsNo]->Get_Draw_Draw_JudgFlg();
}

D3DXVECTOR3 C_GunBase::Get_Draw_Parts_Pol_Pos(const unsigned int * PartsNo, const int * PolNo)
{
	return M_GunParts[*PartsNo]->Get_Draw_Pol_Pos(PolNo);
}

LPD3DXMESH C_GunBase::Get_Draw_Parts_Mesh(const unsigned int * PartsNo)
{
	return M_GunParts[*PartsNo]->Get_Draw_Mesh();
}

bool C_GunBase::Get_Draw_Parts_Iden_Flg(const unsigned int * PartsNo)
{
	if (M_GunParts.size() < 1)return false;

	if ((*PartsNo < 0) || (*PartsNo >= M_GunParts.size()))return false;

	return M_GunParts[*PartsNo]->Get_Draw_Iden_Flg();
}

D3DXMATRIX C_GunBase::Get_Draw_Parts_Draw_Mat(const unsigned int * PartsNo)
{
	return M_GunParts[*PartsNo]->Get_Draw_DrawMat();
}

void C_GunBase::Delete_GunMove(void)
{
	if (M_GunMove != nullptr) delete M_GunMove;
}

void C_GunBase::Draw_GunParts(const D3DXVECTOR3 *CameraPos)
{
	if (M_GunParts.size() < 1)return;

	for (auto && g : M_GunParts) {
		g->Draw_Parts(CameraPos,&Body_DamageFlg);
	}

	Judg_Body_DamageFlg();
}

void C_GunBase::Judg_Rate(void)
{
	if (M_Category_Data.size() < 1) {
		M_S_GunData.RateFlg = false;
		return;
	}

	for (unsigned int c = 0; c < M_Category_Data.size(); c++) {
		if (M_Category_Data[c]->Get_NowRate() > 0) {
			M_S_GunData.RateFlg = true;
			return;
		}
	}

	M_S_GunData.RateFlg = false;
	return;

}
