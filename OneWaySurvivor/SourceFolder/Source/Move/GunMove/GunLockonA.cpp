#include "GunLockonA.h"
#include"GunBulletA.h"

C_GunMove * C_GunLockonA::Action(GUNAI * GunAi)
{
	//Aiが機能しているか
	if(GunAi->AIFlg==false)return nullptr;

	if ((GunAi->AIFlg == true) && (GunAi->RayJudgFlg == false)) {
		//レイ判定可能
		GunAi->RayJudgFlg = true;
		//レイの当たった回数
		GunAi->RayCountNow = GunAi->RayCountInit;
		//射程距離
		GunAi->RayDis = 20.0f;
	}
	//レイの判定回数にいたった時
	if (GunAi->RayCountNow <= 0) {
		//撃つ処理行く
		GunAi->RayJudgFlg = false;
		return new C_GunBulletA();
	}

	GunAi->NowBase.Mat = GunAi->NowBase.Trans*GunAi->ConnectMat;

	D3DXMATRIX StartMat, EndMat,NowMat;
	StartMat = GunAi->Start.RotXMat*(GunAi->Start.RotYMat*GunAi->NowBase.Mat);
	EndMat = GunAi->End.RotXMat*(GunAi->End.RotYMat*GunAi->NowBase.Mat);

	//回転
	if (judg.Quaternion(&NowMat, StartMat, EndMat, &GunAi->NowAnime, GunAi->AnimeFrame, GunAi->GunMoveFlg) == false) {
		GunAi->GunMoveEndFlg = true;
	}
	D3DXVECTOR3 Pos;
	D3DXVec3TransformCoord(&Pos, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &NowMat);
	judg.TarEndMat(&NowMat, GunAi->NowBase.Mat, &GunAi->NowBase.RotX, &GunAi->NowBase.RotY, Pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	return nullptr;
}
