#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"
#include"../../../../GameSource/Count/CountBase.h"

class C_SparkBase :public c_EffectBase
{
public:
	C_SparkBase();
	~C_SparkBase();

	// �X�V����
	bool Update(void);

	// �\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:

	VERTEX v[4];
	LPDIRECT3DTEXTURE9 Tex;
	D3DXMATRIX Mat;

	D3DXMATRIX *PolMat;
	int PolNum;
	float PolSize;  // ����
	
	float yUp, yDown;  // �W�����v�ړ��̕ϐ�
	float zDown;       // �������Ɉړ�������
	C_CountBase *count;// ���Ԃō폜

	bool updateStartFlg;  // �X�V�̊J�n�t���O

	// �W�����v�����̍X�V
	virtual void UpdateMoveY(void);
};