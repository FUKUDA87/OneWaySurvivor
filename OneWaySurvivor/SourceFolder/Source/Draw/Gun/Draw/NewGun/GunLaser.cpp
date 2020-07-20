#include "GunLaser.h"
#include"../../Laser/LaserDraw1.h"

C_GunLaser::~C_GunLaser()
{
	if (mc_Laser != nullptr) {
		delete mc_Laser;
	}
}

void C_GunLaser::Draw(const D3DXVECTOR3 * CameraPos)
{
	Draw_Gun(CameraPos);

	Draw3D_Laser(CameraPos);
}

void C_GunLaser::Draw3D_Laser(const D3DXVECTOR3 * CamPos)
{
	if (mc_Laser == nullptr)return;

	float PolSize = 0.01f;
	bool Flg = false;
	if ((Get_S_GUN_DATA().Ray_Judg_Flg == true) && (Get_S_GUN_DATA().LaserDrawFlg==true))Flg = true;
	mc_Laser->Draw3DAll(&M_S_GunData.DrawBase.Mat, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &PolSize, CamPos, &m_Dis, &Flg);
}

void C_GunLaser::New_Laser(void)
{
	if (mc_Laser != nullptr)return;

	int No = 0;
	mc_Laser = new C_LaserDraw1(&No);

	M_S_GunData.LaserDrawFlg = true;
}

void C_GunLaser::GetDis(const float * Dis)
{
	if (Get_S_GUN_DATA().Ray_Hit_Flg == true) {
		m_Dis = *Dis;
	}
	else {
		m_Dis = Get_S_GUN_DATA().RayDis;
	}
}
