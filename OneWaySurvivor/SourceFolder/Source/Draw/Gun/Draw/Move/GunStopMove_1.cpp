#include "GunStopMove_1.h"

C_GunMoveBase_A * C_GunStopMove_1::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE *Chara)
{
	s_Data->DrawBase.Mat = s_Update->StandMat;

	bool Flg = false;
	Set_PlayerFlg(s_Data, &Flg);

	return nullptr;
}
