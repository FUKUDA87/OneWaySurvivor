#include "Enemy101_Phase7.h"

C_EnemyNo101_Phase7::C_EnemyNo101_Phase7()
{
	GunNo1 = 1;
	InitFlg = true;
}

C_E_AiPhaseBase * C_EnemyNo101_Phase7::Action(const CHARABASE * Chara, std::vector<C_Car_Parts_Joint*> M_Car_Parts, std::vector<C_GunLaser*> M_Gun, S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	if (InitFlg == true) {
		InitFlg = false;

		s_Update->NowPhase = 7;

		if (GunNo1 < M_Gun.size()) {
			M_Gun[GunNo1]->Init_Hp(0, &Co_Damage_No);
		}
	}
	return nullptr;
}
