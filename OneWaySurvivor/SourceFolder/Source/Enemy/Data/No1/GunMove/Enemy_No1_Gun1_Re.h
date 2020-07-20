#pragma once
#include"../../Base&Manager/Enemy_Gun_Move_Base.h"

class C_Enemy_No1_Gun_1_Re :public C_Enemy_Gun_Move_Base {
public:
	C_Enemy_No1_Gun_1_Re();
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	int Count;
};