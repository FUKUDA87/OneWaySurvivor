#pragma once
#include"Sound_2D_Bullet_Hit.h"
#include"../../Base/Sound_Base_3D.h"
#include<string>

class C_Sound_Bullet_Hit_Manager {
public:
	C_Sound_Base_2D* Get_Sound(const S_SOUND_DATA * Data);
private:
	//‚QD‚©‚RD‚Ì”»’è
	C_Sound_Base_2D* Judg_Sound(const S_SOUND_DATA * Data,std::string FileName);
};