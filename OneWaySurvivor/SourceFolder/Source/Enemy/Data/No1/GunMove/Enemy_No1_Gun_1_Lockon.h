#pragma once
#include"../../Base&Manager/Enemy_Gun_Move_Base.h"

class C_Enemy_No1_Gun_1_Lockon:public C_Enemy_Gun_Move_Base {
public:
	C_Enemy_No1_Gun_1_Lockon();
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	bool InitFlg,InitFlg2;//初期化Flg
	QUAMAT Start, End;//回転行列
	float NowAnime, FrameAnime;//回転速度
	int RayCount, RayCountMax;//レイの当たった回数

	void Init(S_GUN_DATA * s_Data,const S_GUN_UPDATE_DATA* s_Update);

	//初期化
	void Init_Init(S_GUN_DATA* s_Data);

	//終了処理
	void End_Move(S_GUN_DATA *s_Data);

	//レイ判定の判定
	bool Ray_Judg(S_GUN_DATA *s_Data);
private:

};