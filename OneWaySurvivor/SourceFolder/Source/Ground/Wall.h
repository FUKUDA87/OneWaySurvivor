#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

class c_Wall {
public:
	c_Wall(const bool *PolygonIdenFlg,const bool *LeftFlg,const D3DXMATRIX *Mat
		,const D3DXVECTOR3 *StartPos,const D3DXVECTOR3 *EndPos);

	// �\��
	void Draw3D();

	//��3D�̍s��n��
	D3DXMATRIX GetMat();

	//�ǂ̏��n��
	S_Base3D_2 GetData();

	//�\���̕ύX
	void SetDrawFlg(const bool *DrawFlg);

	// ������̏������
	S_Capsule GetCapsule(void) { return capsule; }

	// �J�v�Z������
	bool capsuleJudg(float *sd, int *hitNum, const S_Capsule *c);

	// �ǃ��b�V�����C����
	bool MeshRayJudg(float *Dis, const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray);

private:
	//��3D�p
	XFILE_B wallMesh;
	XFILE collisionMesh;

	S_Base3D_2 Wall3D;

	S_Capsule capsule;

	//�ǂ̃T�C�Y�̏�����
	void InitWallSizeZ(const D3DXVECTOR3 * Ground_Vec);

	//��3D�̕\���s��n��
	D3DXMATRIX GetDrawMat();
};