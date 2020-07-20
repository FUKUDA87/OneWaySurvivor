#pragma once
#include"GunLaser.h"

class C_Gun_Init :public C_GunLaser {
public:

protected:
	S_Gun_Parts_Data Get_Data_Set(const bool BulletFlg, const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* MouthPos, const int Rate, const int BulletNo, const int CategoryNo);
};