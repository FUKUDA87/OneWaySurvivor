#include "MatBase.h"
#include"../Judgment.h"

D3DXMATRIX C_MatBase::Set_RotXMat(const float * Ang)
{
	D3DXMATRIX Mat;
	D3DXMatrixRotationX(&Mat, D3DXToRadian(*Ang));
	return Mat;
}

D3DXMATRIX C_MatBase::Set_RotYMat(const float * Ang)
{
	D3DXMATRIX Mat;
	D3DXMatrixRotationY(&Mat, D3DXToRadian(*Ang));
	return Mat;
}

D3DXMATRIX C_MatBase::Set_RotZMat(const float * Ang)
{
	D3DXMATRIX Mat;
	D3DXMatrixRotationZ(&Mat, D3DXToRadian(*Ang));
	return Mat;
}

D3DXMATRIX C_MatBase::Set_TransMat(const D3DXVECTOR3 * Pos)
{
	Judg judg;
	D3DXMATRIX Mat;

	judg.setTransMat(&Mat, Pos);

	return Mat;

}

D3DXMATRIX C_MatBase::Set_ScalMat(const D3DXVECTOR3 * Pos)
{
	Judg judg;
	D3DXMATRIX Mat;
	judg.setScalingMat(&Mat, Pos);
	return Mat;
}

D3DXMATRIX C_MatBase::Init_Mat(void)
{
	D3DXMATRIX L_Mat;
	D3DXMatrixTranslation(&L_Mat, 0.0f, 0.0f, 0.0f);
	return L_Mat;
}
