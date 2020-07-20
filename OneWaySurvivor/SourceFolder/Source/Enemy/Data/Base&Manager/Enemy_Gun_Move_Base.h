#pragma once
#include"../../../Draw/Gun/Draw/Move/GunMoveBase_A.h"
#include"../../../GameSource/Struct.h"

class C_Enemy_Gun_Move_Base :public C_GunMoveBase_A {
public:
	C_Enemy_Gun_Move_Base();

	//e‚ÌXV
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	//•\¦‚Ìs—ñì¬
	void Get_Mat(D3DXMATRIX *Mat, const QUAMAT *Rot, const D3DXMATRIX *StandMat);

	//Ÿ‚Ì“®‚«“n‚µ
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat, const int *NowHp, C_GunMoveBase_A * Move);
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat,const int *NowHp);

	//I—¹ˆ—
	virtual void End_Move(S_GUN_DATA *s_Data);

	//e‚Ì’â~Šm”F
	bool GunStop_Flg(const S_GUN_UPDATE_DATA* s_Update, const CHARABASE *Chara);

private:
	//‘O‰ñ‚ÌXV‚Åe‚ÌHP‚ªƒ[ƒ‚©‚ÌFlg
	bool M_GunInitFlg;

	//e‚Ì‰ñ“]‚Ì‰Šú‰»
	void Init_Gun_RotMat(S_GUN_DATA * s_Data, const int *NowHp);
};