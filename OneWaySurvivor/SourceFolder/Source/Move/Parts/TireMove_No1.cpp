#include "TireMove_No1.h"

C_TireMove_No1::C_TireMove_No1()
{
	AngX = 0.0f;
	AngXMaxUp = 25.0f;
}

C_Move_Parts_Base* C_TireMove_No1::Move(BASE3D * s_Base, const S_CAR_PARTS_DATA * s_Data, const S_GAGE * s_Speed
	, CHARABASE * s_HP, const int * NowPhase, bool * MoveFlg, const D3DXVECTOR3 *ScalPos_Car, const int *I_MoveFlg)
{

	//スピードの率を調べる
	float Size;
	Size = (float)s_Speed->Now / (float)s_Speed->Max;
	//回転させる
	AngX += AngXMaxUp * Size;
	if (AngX > 360.0f)AngX -= 360.0f;
	if (AngX < -360.0f)AngX += 360.0f;

	D3DXMATRIX RotXMat;
	D3DXMatrixRotationX(&RotXMat, D3DXToRadian(AngX));

	s_Base->Mat = Get_PartsMat(s_Data, ScalPos_Car)*s_Base->Mat;

	s_Base->Mat = RotXMat*s_Base->Mat;

	return nullptr;
}
