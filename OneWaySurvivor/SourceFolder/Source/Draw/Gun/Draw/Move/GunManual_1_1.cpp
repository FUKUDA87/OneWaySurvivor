#include "GunManual_1_1.h"
#include"../../../../GameSource/Judgment.h"

C_GunManual_1_1::C_GunManual_1_1()
{
	D3DXMatrixRotationX(&RotXMat, D3DXToRadian(-1.0f));
}

C_GunMoveBase_A * C_GunManual_1_1::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara)
{
	D3DXMATRIX TmpMat;
	Judg judg;
	D3DXVECTOR3 Vec = judg.SetPosM(&s_Update->StandMat);
	Vec += s_Data->DrawBase.TransPos;
	judg.setTransMat(&TmpMat, &Vec);
	s_Data->DrawBase.Mat = s_Update->CameraMat*RotXMat*TmpMat;

	bool Flg = true;
	Set_PlayerFlg(s_Data, &Flg);

	return nullptr;
}
