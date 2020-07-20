#include "CarBulletManager.h"
#include"../Draw/Bullet/Bullet_DrawManager.h"

C_CarBulletManager::~C_CarBulletManager()
{
	AllDelete();
}

bool C_CarBulletManager::Update_ALL_Bullet(void)
{
	MoveVecBullet();
	Shot();
	UpdateBullet();

	return true;
}

void C_CarBulletManager::AllDelete(void)
{
	if (GetBulletNum() < 1) return;

	for (unsigned int b = 0; b < GetBulletNum(); b++) {
		DeleteBullet(&b);
	}
}

void C_CarBulletManager::DeleteBullet(unsigned int * NowBulletNo)
{
	if (Bullet_NoJudg(NowBulletNo) != true)return;

	unsigned int No = *NowBulletNo;

	delete bullet[No];
	bullet.erase(bullet.begin() + No);
	No--;

	*NowBulletNo = No;


}

bool C_CarBulletManager::Bullet_NoJudg(const unsigned int * NowBulletNo)
{
	if (GetBulletNum() < 1) return false;
	unsigned int No = *NowBulletNo;
	if (No < 0)return false;
	if (No >= GetBulletNum())return false;

	return true;
}

D3DXMATRIX C_CarBulletManager::Get_Bullet_Mat(const unsigned int * BulletNo)
{
	return bullet[*BulletNo]->Get_BASE3D().Mat;
}

bool C_CarBulletManager::UpdateBullet(void)
{
	if (bullet.size() < 1)return false;

	for (unsigned int b = 0; b < bullet.size();b++) {
		if (bullet[b]->Move() != true) {
			delete bullet[b];
			bullet.erase(bullet.begin() + b);
			b--;
		}
	}

	return true;
}

void C_CarBulletManager::Draw_Bullet(const D3DXVECTOR3 * CameraPos)
{
	if (bullet.size() < 1)return ;

	for (auto && b : bullet)b->Draw(CameraPos);
	
}

void C_CarBulletManager::MoveVecBullet(void)
{
	if (bullet.size() < 1)return;

	for (auto && b : bullet)b->MoveVec(&brj.MoveVec);
}

void C_CarBulletManager::Shot(void)
{
	if (gun.size() < 1)return;

	C_Bullet_DrawManager Bullet_Manager;

	for (unsigned int g = 0; g < gun.size(); g++) {
		gun[g]->Init_Departure_Num();
		for (unsigned int i = 0; i < gun[g]->Get_CategoryNum(); i++) {
			if (gun[g]->Get_TriggerFlg(&i) == true) {
				int b = gun[g]->Get_BulletNo();
				D3DXMATRIX Mat = gun[g]->Get_GunMouth_Mat(&i);

				bullet.push_back(Bullet_Manager.Get_Bullet(&b, &Mat));
				gun[g]->Bullet_Shot_Update(&i);
				ShotEffect(&g, &i);
			}
		}
	}
}

bool C_CarBulletManager::GetBulletGroWalJudgFlg(const unsigned int * BulletNo)
{
	return bullet[*BulletNo]->Get_GroWal_Judg_Flg();
}

void C_CarBulletManager::SetBulletGroWalJudgFlg(const unsigned int * BulletNo, const bool * Flg)
{
	bullet[*BulletNo]->Set_GroWal_Jufg_Flg(Flg);
}

void C_CarBulletManager::GetBulletMoveData(BULLETJUDGDATA * Bullet, RAYDATA * BulletRay,const unsigned int *bc)
{
	//‰Šú‰»
	float Dis;
	int carType = GetConstCar();

	Dis = bullet[*bc]->Get_S_BULLET().Speed;

	c_StructManager structManager;
	*Bullet = structManager.GetBULLETJUDGDATA(&structManager.GetCarType(&carType), &Dis);

	BulletRay->Mat= bullet[*bc]->Get_BASE3D().Mat;
	D3DXVec3TransformNormal(&BulletRay->Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay->Mat);
}

void C_CarBulletManager::ShotEffect(const unsigned int * gc, const unsigned int * mc)
{
	int effectNum = gun[*gc]->GetShotEffectNum();

	if (effectNum <= 0)return;

	for (int ec = 0; ec < effectNum; ec++)
	{
		NewEffect(gun[*gc]->GetShotEffect(&ec, mc));
	}
}
