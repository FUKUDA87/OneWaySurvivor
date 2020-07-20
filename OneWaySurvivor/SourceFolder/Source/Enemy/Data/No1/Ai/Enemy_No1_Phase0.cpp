#include "Enemy_No1_Phase0.h"
#include"ENo1_AiPhase.h"

C_E_AiPhaseBase * C_E_No1_Phase0::Action(const CHARABASE * Chara, std::vector<C_Car_Parts_Joint*>M_Car_Parts, std::vector<C_GunLaser*> M_Gun, S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	s_Update->NowPhase = 0;

	if (*GroNo > *Traget_GroNo - 2)return new C_E_No1_AiPhase();

	return nullptr;
}
