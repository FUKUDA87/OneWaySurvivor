#include "Ene_1_Gun_1_Stop.h"
#include"Enemy_No1_Gun1_Re.h"

C_GunMoveBase_A * C_Ene_1_Gun_1_Stop::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE * Chara)
{
	if (s_Update->Gun_Stop_Flg == true)return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp);

	if (Chara->NowHp > 0) {
		return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp, new C_Enemy_No1_Gun_1_Re());
	}

	return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp);
}
