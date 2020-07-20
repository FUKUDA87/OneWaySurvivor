#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Move_Parts_Base {
public:
	virtual C_Move_Parts_Base* Move(BASE3D *s_Base, const S_CAR_PARTS_DATA *s_Data, const S_GAGE *s_Speed,CHARABASE *s_HP
		, const int *NowPhase,bool *MoveFlg, const D3DXVECTOR3 *ScalPos_Car,const int *I_MoveFlg) = 0;
protected:
	D3DXMATRIX Get_PartsMat(const S_CAR_PARTS_DATA *s_Data, const D3DXVECTOR3 *ScalPos_Car);
};