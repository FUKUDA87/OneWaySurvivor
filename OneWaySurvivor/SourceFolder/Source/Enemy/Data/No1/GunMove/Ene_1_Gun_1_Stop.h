#pragma once
#include"../../Base&Manager/Enemy_Gun_Move_Base.h"

class C_Ene_1_Gun_1_Stop :public C_Enemy_Gun_Move_Base {
public:
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
};