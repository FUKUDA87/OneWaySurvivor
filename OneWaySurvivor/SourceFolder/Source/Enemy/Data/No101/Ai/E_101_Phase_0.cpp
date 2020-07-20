#include "E_101_Phase_0.h"
#include"ENo101_AiPhase_1.h"
/*
フェーズ０：準備
Speed側で所定の位置に着くとフェーズ１
フェーズ１：銃(1)の回転
銃(1)のHpが０になるとフェーズ２
フェーズ２：ドアのオープン、銃(２)の回転、本体HP減少true
本体Hpが６６％以下になればフェーズ３
フェーズ３：フェーズ１と同じ
フェーズ４で本体Hpが33％以下になればフェーズ５
フェーズ6で本体Hpが0になればフェーズ７

*/

C_E_No101_Phase_0::C_E_No101_Phase_0()
{
	InitFlg = true;
}

C_E_AiPhaseBase * C_E_No101_Phase_0::Action(const CHARABASE * Chara,
	std::vector<C_Car_Parts_Joint*> M_Car_Parts, std::vector<C_GunLaser*> M_Gun,
	S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	if (InitFlg == true) {
		InitFlg = false;
		s_Update->NowPhase = 0;
	}

	if (*GroNo > *Traget_GroNo-2)return new C_E_No101_AiPhase_1();

	return nullptr;
}
