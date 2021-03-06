#pragma once
#include"../../EffectBase.h"

class c_MuzzleFlash :public c_EffectBase
{
public:
	c_MuzzleFlash(const D3DXMATRIX *Gun_Mouth_Mat);

	// 更新処理
	bool Update(const s_CarEffectUpdateData *updateData);

	// 表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);
private:
	bool AliveFlg;

	TEXTURE tex;

	VERTEX v[4];

	D3DXMATRIX mat;
};