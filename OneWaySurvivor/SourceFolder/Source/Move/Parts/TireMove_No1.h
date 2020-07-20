#pragma once
#include"Move_Parts_Base.h"

class C_TireMove_No1 :public C_Move_Parts_Base {
public:
	C_TireMove_No1();
	C_Move_Parts_Base* Move(BASE3D *s_Base, const S_CAR_PARTS_DATA *s_Data, const S_GAGE *s_Speed, CHARABASE *s_HP
		, const int *NowPhase, bool *MoveFlg, const D3DXVECTOR3 *ScalPos_Car, const int *I_MoveFlg);
protected:
	float AngX, AngXMaxUp;
};