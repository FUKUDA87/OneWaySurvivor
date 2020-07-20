#include "DamageNumDraw3DManager.h"
#include"../../GameSource/Judgment.h"
#include"Damage_Move_B.h"
#include"../../GameSource/Const.h"

c_DamageNumDraw3DManager::~c_DamageNumDraw3DManager()
{
	if (damageNumDraw.size() <= 0)return;

	for (unsigned int vc = 0; vc < damageNumDraw.size(); vc++)
	{
		delete damageNumDraw[vc];
		damageNumDraw.erase(damageNumDraw.begin() + vc);
		vc--;
	}
}

bool c_DamageNumDraw3DManager::Update(void)
{
	if (damageNumDraw.size() <= 0)return false;

	for (unsigned int vc = 0; vc < damageNumDraw.size(); vc++)
	{
		if (damageNumDraw[vc]->Update() != true)
		{
			delete damageNumDraw[vc];
			damageNumDraw.erase(damageNumDraw.begin() + vc);
			vc--;
		}
	}

	return true;
}

void c_DamageNumDraw3DManager::Draw2D(void)
{
	if (damageNumDraw.size() <= 0)return;

	for (auto && v : damageNumDraw) v->Draw_2D();
}

void c_DamageNumDraw3DManager::UpdatePos2D(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport, const D3DXMATRIX * PlayerJudgMat)
{
	if (damageNumDraw.size() <= 0)return;

	D3DXVECTOR3 Pos3D, Pos2D;
	Judg judg;

	for (auto && v : damageNumDraw) {

		Pos3D = v->Get_Pos_3D(PlayerJudgMat);

		judg.Pos2D(&Pos2D, &Pos3D, mProj, mView, Viewport);

		v->Set_Pos_2D(&Pos2D);

	}

}

void c_DamageNumDraw3DManager::NewDamageNumDraw(const int * Character_Type, const D3DXMATRIX * Ray_Mat, const D3DXVECTOR3 * Ray_Vec
	, const float * Ray_Dis, const int * Damage, const bool * DamageFlg, const D3DXMATRIX *PlayerJudgMat)
{
	return;//”ñ•\Ž¦’†

	if (*Character_Type != co_PlayerCar) return;

	if (*DamageFlg != true)return;

	Judg judg;

	D3DXVECTOR3 RayHitPos;

	judg.GetRayHitPos(&judg.SetPosM(Ray_Mat), Ray_Vec, Ray_Dis);

	int L_Damage = *Damage;
	if (*DamageFlg != true)L_Damage = 0;

	damageNumDraw.push_back(new C_Damage_Move_B(&RayHitPos, PlayerJudgMat, &L_Damage));
}
