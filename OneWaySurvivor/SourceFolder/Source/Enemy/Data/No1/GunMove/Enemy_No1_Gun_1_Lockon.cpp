#include "Enemy_No1_Gun_1_Lockon.h"
#include"Enemy_No1_Gun_1_Shot.h"
#include"Ene_1_Gun_1_Stop.h"

C_Enemy_No1_Gun_1_Lockon::C_Enemy_No1_Gun_1_Lockon()
{
	InitFlg = true;
	RayCount=RayCountMax = 20;
	InitFlg2 = true;
}

C_GunMoveBase_A * C_Enemy_No1_Gun_1_Lockon::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE *Chara)
{
	s_Data->BulletFlg = false;

	if (s_Update->NowPhase <= Phase0)return Get_Move(s_Data, &s_Update->StandMat,&Chara->NowHp);

	if(GunStop_Flg(s_Update,Chara))return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp,new C_Ene_1_Gun_1_Stop());

	//if(s_Data->MoveFlg!=true)

	Init_Init(s_Data);

	s_Data->Ray_Judg_Flg = true;

	if(Ray_Judg(s_Data)!=true)return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp, new C_Enemy_No1_Gun_1_Shot());

	Init(s_Data, s_Update);

	//if (s_Data->RayJudgFlg != true)return nullptr;

	Judg judg;

	bool MoveFlg=true;

	//‰ñ“]
	if (judg.AnimeFrameInc(&NowAnime, &FrameAnime, &MoveFlg) == true) {
		//if (s_Data->RayHitFlg != true) {
		InitFlg = true;
		//}
	}


	judg.AnimeQua(&s_Data->NowRot.RotXMat, &Start.RotXMat, &End.RotXMat, &NowAnime);

	judg.AnimeQua(&s_Data->NowRot.RotYMat, &Start.RotYMat, &End.RotYMat, &NowAnime);

	return Get_Move(s_Data, &s_Update->StandMat, &Chara->NowHp);
}

void C_Enemy_No1_Gun_1_Lockon::Init(S_GUN_DATA * s_Data,const S_GUN_UPDATE_DATA * s_Update)
{
	if (InitFlg != true)return;

	InitFlg = false;

	//‰ñ“]‚Ì‰Šú‰»

	Start.RotXMat = s_Data->NowRot.RotXMat;
	Start.RotYMat = s_Data->NowRot.RotYMat;

	D3DXMATRIX TmpMat;
	TmpMat =s_Update->StandMat;

	Judg judg;

	judg.TarEndMat(&TmpMat, TmpMat, &End.RotXMat, &End.RotYMat, s_Update->TargetPos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	NowAnime = 0.0f;
	FrameAnime = 0.05f;
}

void C_Enemy_No1_Gun_1_Lockon::Init_Init(S_GUN_DATA * s_Data)
{
	if (InitFlg2 != true)return;

	InitFlg2 = false;

	s_Data->RayDis = 30;
}

void C_Enemy_No1_Gun_1_Lockon::End_Move(S_GUN_DATA * s_Data)
{
	s_Data->Ray_Judg_Flg = false;
}

bool C_Enemy_No1_Gun_1_Lockon::Ray_Judg(S_GUN_DATA * s_Data)
{
	if (s_Data->Ray_Hit_Flg != true) return true;

	RayCount--;

	if (RayCount > 0) return true;

	RayCount = 0;


	if (InitFlg != true)return true;

	return false;
}
