#include "StopMove.h"

C_Move_Parts_Base * C_StopMove::Move(BASE3D * s_Base, const S_CAR_PARTS_DATA * s_Data
	, const S_GAGE * s_Speed, CHARABASE * s_HP, const int * NowPhase, bool * MoveFlg, const D3DXVECTOR3 *ScalPos_Car, const int *I_MoveFlg)
{
	
	s_Base->Mat = Get_PartsMat(s_Data, ScalPos_Car)*s_Base->Mat;

	return nullptr;
}
