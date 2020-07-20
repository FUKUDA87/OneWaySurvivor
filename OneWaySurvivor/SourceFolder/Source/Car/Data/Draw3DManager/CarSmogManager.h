#pragma once
#include"CarMeshManager.h"

class C_CarSmogManager {
public:
	//���̏o���ʒu
	D3DXMATRIX GetPos(const int *CarNo);
	//���̃A�j���[�V�������@
	S_Smoke GetSmog(const int *CarNo);
private:
	//���̍\���̂̏�����
	S_Smoke GetInitSmog(const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *Frame, const int Alpha, const int AStart, const int ADown, const float PolSize, const float PolBit, const float PolBitUp, const S_Random *Random);
};