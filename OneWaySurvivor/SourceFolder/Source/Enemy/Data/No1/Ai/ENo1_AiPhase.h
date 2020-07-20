#pragma once
#include"../../Base&Manager/EnemyAiPhaseBase.h"

class C_E_No1_AiPhase:public C_E_AiPhaseBase {
public:
	C_E_No1_AiPhase();
	C_E_AiPhaseBase* Action(const CHARABASE *Chara, std::vector<C_Car_Parts_Joint*>M_Car_Parts, std::vector<C_GunLaser*>M_Gun, S_GUN_UPDATE_DATA* s_Update, const unsigned int *GroNo, const unsigned int *Traget_GroNo);
protected:
private:
	//‰Šú‰»ƒtƒ‰ƒO
	bool InitFlg;
};