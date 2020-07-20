#pragma once
#include"../../EffectBase.h"
#include"../../../../GameSource/Count/Count.h"

class c_EmptyBullet :public c_EffectBase
{
public:
	c_EmptyBullet(const D3DXMATRIX *GunMat);
	~c_EmptyBullet();

	// 更新処理
	bool Update(const s_CarEffectUpdateData *updateData);

	// 表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);
private:
	D3DXMATRIX mat;

	XFILE mesh;

	//移動ベクトル
	D3DXVECTOR3 moveVec;
	//yの減らす量
	float yDown;

	C_Count *count;

	float scalSize;
};