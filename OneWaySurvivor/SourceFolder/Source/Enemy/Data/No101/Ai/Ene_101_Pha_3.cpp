#include "Ene_101_Pha_3.h"
#include"Enemy101_Phase4.h"
#include"Enemy101_Phase5.h"
#include"Enemy101_Phase7.h"

C_EnemyNo101_Phase3::C_EnemyNo101_Phase3()
{
	GunNo0 = 0;
	GunNo1 = 1;
	InitFlg = true;
}

C_E_AiPhaseBase * C_EnemyNo101_Phase3::Action(const CHARABASE * Chara, std::vector<C_Car_Parts_Joint*> M_Car_Parts, std::vector<C_GunLaser*> M_Gun, S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	//初期化
	if (InitFlg == true) {
		InitFlg = false;

		s_Update->NowPhase = 3;

		if (GunNo0 < M_Gun.size()) {
			M_Gun[GunNo0]->Init_Hp(20, &Co_Damage_Yes);
		}

		if (GunNo1 < M_Gun.size()) {
			M_Gun[GunNo1]->Init_Hp(0, &Co_Damage_No);
		}
		for (auto && p : M_Car_Parts) {
			if ((p->Get_Parts_Data().MeshTypeNo == Co_Parts_Judg) && (p->Get_Parts_Data().MeshJointNo == 1))p->Init_Hp(1, &Co_Damage_No);
			if ((p->Get_Parts_Data().MeshTypeNo == Co_Parts_Judg) && (p->Get_Parts_Data().MeshJointNo == 2))p->SetDamageFlg(&Co_Damage_No);
		}
	}

	//銃の引き金を入れる
	if (GunNo0<M_Gun.size()) {
		bool L_Flg = true;
		M_Gun[GunNo0]->Update_Trigger(&L_Flg);
	}

	//車のドアの操作
	if (M_Car_Parts.size() > 0) {
		for (unsigned int p = 0; p < M_Car_Parts.size(); p++) {
			if (M_Car_Parts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Door) {
				M_Car_Parts[p]->Set_I_MoveFlg(2);
			}
		}
	}

	//Hpの割合でフェーズ変更
	float Hp = (float)Chara->NowHp, MaxHp = (float)Chara->MaxHp;
	float S = Hp / MaxHp;
	if (S < 0.34f) {
		if (Chara->NowHp <= 0) {
			return new C_EnemyNo101_Phase7();
		}
		else {
			return new C_EnemyNo101_Phase5();
		}
	}

	//銃が死んだ時にフェーズ変更
	if (GunNo0 < M_Gun.size()) {
		if (M_Gun[GunNo0]->Dead() == true)return new C_EnemyNo101_Phase4();
	}


	return nullptr;
}
