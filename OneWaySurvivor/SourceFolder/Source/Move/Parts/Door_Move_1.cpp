#include "Door_Move_1.h"
#include"../../GameSource/Judgment.h"

C_Door_Move_1::C_Door_Move_1(const float * MoveAng, const float *Frame, const float *Anime)
{
	M_AngY = *MoveAng;
	M_Frame = *Frame;
	M_Anime = *Anime;

	InitFlg = true;
}

C_Move_Parts_Base * C_Door_Move_1::Move(BASE3D * s_Base, const S_CAR_PARTS_DATA * s_Data, const S_GAGE * s_Speed, CHARABASE * s_HP
	, const int * NowPhase, bool * MoveFlg, const D3DXVECTOR3 * ScalPos_Car, const int *I_MoveFlg)
{
	Init(s_Base, s_Data);

	DoorMove(&s_Base->RotY, I_MoveFlg);

	s_Base->Mat = Get_PartsMat(s_Data, ScalPos_Car)*s_Base->Mat;

	s_Base->Mat = s_Base->RotY *s_Base->Mat;

	return nullptr;
}

void C_Door_Move_1::Init(BASE3D * s_Base, const S_CAR_PARTS_DATA * s_Data)
{
	if (InitFlg != true)return;

	int i = 0;
	DoorMove(&s_Base->RotY, &i);

	InitFlg = false;
}

void C_Door_Move_1::DoorMove(D3DXMATRIX* Mat,const int *I_MoveFlg)
{

	D3DXMATRIX StartMat, EndMat,NowMat;

	D3DXMatrixRotationY(&StartMat, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&EndMat, D3DXToRadian(M_AngY));

	Judg judg;

	float F = M_Frame;
	if (*I_MoveFlg == 2)F *= -1.0f;
	if (*I_MoveFlg == 0)F = 0.0f;

	judg.Quaternion(&NowMat, StartMat, EndMat, &M_Anime, F, true);

	*Mat=NowMat;
}
