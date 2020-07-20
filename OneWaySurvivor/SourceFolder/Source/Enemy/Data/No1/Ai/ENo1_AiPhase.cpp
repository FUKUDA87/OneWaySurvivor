#include "ENo1_AiPhase.h"

C_E_No1_AiPhase::C_E_No1_AiPhase()
{
	InitFlg = true;
}

C_E_AiPhaseBase * C_E_No1_AiPhase::Action(const CHARABASE *Chara, std::vector<C_Car_Parts_Joint*>M_Car_Parts, std::vector<C_GunLaser*>M_Gun, S_GUN_UPDATE_DATA* s_Update, const unsigned int *GroNo, const unsigned int *Traget_GroNo)
{
	s_Update->NowPhase = 1;

	if (InitFlg == true) {
		InitFlg = false;

		//M_Gun[0]->Init_Hp(1, &Co_Damage_Yes);
		/*for (auto && p : M_Car_Parts) {
			p->Init_Hp(1, &Co_Damage_Yes);
		}*/
	}

	bool Flg = true;
	if (M_Gun.size() > 0)M_Gun[0]->Update_Trigger(&Flg);
	return nullptr;
}
