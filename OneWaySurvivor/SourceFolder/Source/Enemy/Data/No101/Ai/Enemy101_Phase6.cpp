#include "Enemy101_Phase6.h"
#include "Enemy101_Phase7.h"

C_EnemyNo101_Phase6::C_EnemyNo101_Phase6()
{
	GunNo1 = 1;
	InitFlg = true;
}

C_E_AiPhaseBase * C_EnemyNo101_Phase6::Action(const CHARABASE * Chara, std::vector<C_Car_Parts_Joint*> M_Car_Parts, std::vector<C_GunLaser*> M_Gun, S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	//初期化
	if (InitFlg == true) {
		InitFlg = false;

		s_Update->NowPhase = 6;

		if (GunNo1 < M_Gun.size()) {
			M_Gun[GunNo1]->Init_Hp(1, &Co_Damage_No);
		}
		for (auto && p : M_Car_Parts) {
			if ((p->Get_Parts_Data().MeshTypeNo == Co_Parts_Judg) && (p->Get_Parts_Data().MeshJointNo == 1))p->Init_Hp(1, &Co_Damage_No_Parts);
			if ((p->Get_Parts_Data().MeshTypeNo == Co_Parts_Judg) && (p->Get_Parts_Data().MeshJointNo == 2))p->SetDamageFlg(&Co_Damage_No_Parts);
		}
	}

	//銃の引き金の操作
	if (GunNo1 < M_Gun.size()) {
		bool L_Flg = true;
		M_Gun[GunNo1]->Update_Trigger(&L_Flg);
	}

	//車のドアの操作
	if (M_Car_Parts.size() > 0) {
		for (unsigned int p = 0; p < M_Car_Parts.size(); p++) {
			if (M_Car_Parts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Door) {
				M_Car_Parts[p]->Set_I_MoveFlg(1);
			}
		}
	}

	//Hpの割合でフェーズ変更
	if (Chara->NowHp <= 0) {
		return new C_EnemyNo101_Phase7();
	}


	return nullptr;
}
