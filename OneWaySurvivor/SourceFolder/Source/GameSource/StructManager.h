#pragma once
#include"Struct.h"

class c_StructManager
{
public:
	s_CarType GetCarType(const int *Type, const unsigned int *Number1, const unsigned int *Number2, const unsigned int *Number3);
	s_CarType GetCarType(const int *Type, const unsigned int *Number1, const unsigned int *Number2);
	s_CarType GetCarType(const int *Type, const unsigned int *Number1);
	s_CarType GetCarType(const int *Type);

	BULLETJUDGDATA GetBULLETJUDGDATA(const s_CarType *carType, const float *Dis);

	// �J�v�Z���̍쐬
	S_Capsule getCapsule(const D3DXMATRIX *m, const D3DXVECTOR3 *scal, const D3DXVECTOR3 *meshBigVec, const D3DXVECTOR3 *meshSmallVec);

private:
	// vecInit��vecJudg��������
	bool capsuleVecInit(D3DXVECTOR3 *vi,D3DXVECTOR3 *vj, float *r, const D3DXMATRIX *m, const D3DXVECTOR3 *scal, const D3DXVECTOR3 *meshVec);
};