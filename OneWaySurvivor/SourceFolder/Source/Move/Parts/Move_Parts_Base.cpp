#include "Move_Parts_Base.h"
#include"../../GameSource/Judgment.h"

D3DXMATRIX C_Move_Parts_Base::Get_PartsMat(const S_CAR_PARTS_DATA * s_Data, const D3DXVECTOR3 * ScalPos_Car)
{
	D3DXMATRIX RotX, RotY, RotZ, Trans;

	D3DXMatrixRotationX(&RotX, D3DXToRadian(s_Data->Ang.x));
	D3DXMatrixRotationY(&RotY, D3DXToRadian(s_Data->Ang.y));
	D3DXMatrixRotationZ(&RotZ, D3DXToRadian(s_Data->Ang.z));

	Judg judg;

	judg.setTransMat(&Trans, &judg.GetVecVec(&s_Data->TransPos, ScalPos_Car));

	D3DXMATRIX Mat;

	Mat = RotX * RotY*RotZ*Trans;

	return Mat;
}
