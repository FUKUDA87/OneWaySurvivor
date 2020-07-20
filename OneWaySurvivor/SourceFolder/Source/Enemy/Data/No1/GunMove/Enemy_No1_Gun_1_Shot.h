#pragma once
#include"../../Base&Manager/Enemy_Gun_Move_Base.h"

class C_Enemy_No1_Gun_1_Shot :public C_Enemy_Gun_Move_Base {
public:
	C_Enemy_No1_Gun_1_Shot();
	~C_Enemy_No1_Gun_1_Shot();

	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	C_Departure_Gun_Auto_Base *M_Move;
private:
	bool InitFlg;

	void Init(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update);
};