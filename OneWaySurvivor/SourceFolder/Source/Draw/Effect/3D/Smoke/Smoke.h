#pragma once
#include<d3dx9.h>
#include"../../../../GameSource/Struct.h"
#include"../../EffectBase.h"
#include"../../../../GameSource/Count/CountBase.h"

class c_Smoke:public c_EffectBase {
public:
	c_Smoke(const int *CarNo,const D3DXMATRIX *Mat, const float *HpPer, const int *NowHp);
	~c_Smoke();

	// �X�V����
	bool Update(const s_CarEffectUpdateData *updateData);
	
	//�\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);

private:
	S_Polygon smokePol;
	//�����폜�p
	C_CountBase *count;

	// ���̎��
	int Draw_No;

	//�\�����@�̍\����
	S_Smoke smoke;

	//�����x�̃A�b�v�f�[�g
	void Update_Alpha(void);
	//�����̐��l�쐬
	float RandPlus(const int *Num);
	//�|���S���T�C�Y�̕ω�
	float GetPolSize(void);

	// ���̔Z��
	int InitDrawNo(const float *HpPer, const int *NowHp);
};