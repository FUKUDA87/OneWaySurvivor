#pragma once
#include"Move_Parts_Base.h"

class C_Door_Move_1 :public C_Move_Parts_Base {
public:
	C_Door_Move_1(const float *MoveAng,const float *Frame, const float *Anime);
	C_Move_Parts_Base* Move(BASE3D *s_Base, const S_CAR_PARTS_DATA *s_Data, const S_GAGE *s_Speed, CHARABASE *s_HP, const int *NowPhase, bool *MoveFlg, const D3DXVECTOR3 *ScalPos_Car
		, const int *I_MoveFlg);
protected:
	float M_AngY,M_Frame,M_Anime;
	bool InitFlg;

	void Init(BASE3D *s_Base, const S_CAR_PARTS_DATA *s_Data);

	void DoorMove(D3DXMATRIX* Mat,const int *I_MoveFlg);
};