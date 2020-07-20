#pragma once
#include"../../EffectBase.h"

class c_MuzzleFlash :public c_EffectBase
{
public:
	c_MuzzleFlash(const D3DXMATRIX *Gun_Mouth_Mat);

	// çXêVèàóù
	bool Update(const s_CarEffectUpdateData *updateData);

	// ï\é¶
	void Draw3D(const D3DXVECTOR3 *CameraPos);
private:
	bool AliveFlg;

	TEXTURE tex;

	VERTEX v[4];

	D3DXMATRIX mat;
};