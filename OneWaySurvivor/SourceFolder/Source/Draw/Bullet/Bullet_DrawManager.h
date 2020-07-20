#pragma once
#include"Bullet_No1.h"

class C_Bullet_DrawManager {
public:
	C_Bullet_Base* Get_Bullet(const int *BulletNo, const D3DXMATRIX *Mat);
	C_Bullet_Base* Get_Bullet(const int *BulletNo, const D3DXMATRIX *Mat, const S_RayHitJudgData* RayData);
};