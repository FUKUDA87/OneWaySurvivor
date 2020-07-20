#include "Enemy_Gun_Move_Base.h"

C_Enemy_Gun_Move_Base::C_Enemy_Gun_Move_Base()
{
	M_GunInitFlg = true;
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE * Chara)
{
	return nullptr;
}

void C_Enemy_Gun_Move_Base::Get_Mat(D3DXMATRIX * Mat, const QUAMAT * Rot, const D3DXMATRIX * StandMat)
{
	*Mat = Rot->RotXMat*(Rot->RotYMat*(*StandMat));
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX * StandMat, const int * NowHp, C_GunMoveBase_A * Move)
{
	//銃の回転の初期化
	Init_Gun_RotMat(s_Data,NowHp);

	//今回の動きの終了処理
	if (Move != nullptr) End_Move(s_Data);

	//表示行列の合成
	Get_Mat(&s_Data->DrawBase.Mat, &s_Data->NowRot, StandMat);

	return Move;
}

C_GunMoveBase_A * C_Enemy_Gun_Move_Base::Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX * StandMat, const int * NowHp)
{
	return Get_Move(s_Data, StandMat,NowHp, nullptr);
}

void C_Enemy_Gun_Move_Base::End_Move(S_GUN_DATA * s_Data)
{
}

bool C_Enemy_Gun_Move_Base::GunStop_Flg(const S_GUN_UPDATE_DATA * s_Update, const CHARABASE * Chara)
{
	if (s_Update->Gun_Stop_Flg == true)return true;

	if (Chara->NowHp <= 0)return true;

	return false;
}

void C_Enemy_Gun_Move_Base::Init_Gun_RotMat(S_GUN_DATA * s_Data, const int * NowHp)
{
	if (NowHp > 0) {
		if (M_GunInitFlg == true)return;

		//回転初期化FlgをHPがある状態を表すtrueにする
		M_GunInitFlg = true;

		return;
	}

	if (M_GunInitFlg != true)return;

	//回転の初期化
	D3DXMatrixRotationX(&s_Data->NowRot.RotXMat, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&s_Data->NowRot.RotYMat, D3DXToRadian(0.0f));

	//回転初期化FlgをHPがゼロである状態を表すfalseにする
	M_GunInitFlg = false;
}

