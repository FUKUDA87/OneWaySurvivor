#pragma once
#include"../../EffectBase.h"
#include"../../../../GameSource/Count/Count.h"

class c_EmptyBullet :public c_EffectBase
{
public:
	c_EmptyBullet(const D3DXMATRIX *GunMat);
	~c_EmptyBullet();

	// �X�V����
	bool Update(const s_CarEffectUpdateData *updateData);

	// �\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);
private:
	D3DXMATRIX mat;

	XFILE mesh;

	//�ړ��x�N�g��
	D3DXVECTOR3 moveVec;
	//y�̌��炷��
	float yDown;

	C_Count *count;

	float scalSize;
};