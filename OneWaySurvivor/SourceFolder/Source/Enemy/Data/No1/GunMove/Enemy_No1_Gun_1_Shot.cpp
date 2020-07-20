#include "Enemy_No1_Gun_1_Shot.h"
#include"Enemy_No1_Gun1_Re.h"
#include"Ene_1_Gun_1_Stop.h"

C_Enemy_No1_Gun_1_Shot::C_Enemy_No1_Gun_1_Shot()
{
	InitFlg = true;
}

C_Enemy_No1_Gun_1_Shot::~C_Enemy_No1_Gun_1_Shot()
{
	if (M_Move == nullptr)return;

	delete M_Move;
}

C_GunMoveBase_A * C_Enemy_No1_Gun_1_Shot::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE *Chara)
{
	Init(s_Data,s_Update);

	if (GunStop_Flg(s_Update, Chara))return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp, new C_Ene_1_Gun_1_Stop());

	bool Flg = M_Move->Get_BulletFlg(&s_Data->Departure_Num);

	s_Data->BulletFlg = Flg;
	
	if (Flg != true)return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp,new C_Enemy_No1_Gun_1_Re());

	return Get_Move(s_Data,&s_Update->StandMat, &Chara->NowHp);
}

void C_Enemy_No1_Gun_1_Shot::Init(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update)
{
	if (InitFlg != true)return;

	InitFlg = false;

	M_Move=Get_Departure(&s_Data->Depar);
}
