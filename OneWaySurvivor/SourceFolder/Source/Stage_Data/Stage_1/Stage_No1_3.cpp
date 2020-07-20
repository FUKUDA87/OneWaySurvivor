#include "Stage_No1_3.h"

C_Stage_No1_3::C_Stage_No1_3()
{
	M_Stage_Data.WaveType_Now = Co_Wave_Type_Boss;

	M_BossWay_Number = 2;

	New_Car_Data(co_EnemyCar, 101, 0, -8, M_BossWay_Number);
}

void C_Stage_No1_3::M_Car_Pop_Update(std::vector<C_EnemyAi*> enemy)
{
	//出現している敵がいない場合にボス以外の出現情報を消す。
	if (enemy.size() <= 0) {
		M_EnemyCar_Delete();
		return;
	}

	//ボスが出現している際に敵を出現させる
	if (enemy.size() <= 2) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if ((enemy[e]->Get_BossFlg() == true) && (enemy[e]->GetFlgCar() == true)) {

				//車線番号
				int L_Way_Number = M_BossWay_Number;

				switch (enemy[e]->Get_Gun_Update_Data().NowPhase)
				{
				case 4:

					if ((M_Car_Data.size() > 0) || (enemy.size() >= 2)) break;

					while (L_Way_Number == M_BossWay_Number)L_Way_Number = rand() % 5;

					New_Car_Data(co_EnemyCar, 1, 60, -8, L_Way_Number);

					break;

				case 6:

					if ((M_Car_Data.size() > 0) || (enemy.size() >= 3)) break;

					while (L_Way_Number == M_BossWay_Number)L_Way_Number = rand() % 5;

					New_Car_Data(co_EnemyCar, 1, 60, -8, L_Way_Number);

					break;
				}

				return;
			}
		}
	}

	return;
}

C_Car_Pop_Base * C_Stage_No1_3::Next_Pop(void)
{
	M_Stage_Data.WaveType_Now = Co_Wave_Type_End;
	return nullptr;
}

void C_Stage_No1_3::M_EnemyCar_Delete(void)
{
	if (M_Car_Data.size() <= 0)return;

	//ボス以外の車の出現情報削除
	for (unsigned int d = 0; d < M_Car_Data.size(); d++) {
		if ((M_Car_Data[d]->Get_Data().CarType == co_EnemyCar) && (M_Car_Data[d]->Get_Data().CarNo < 100))continue;
		delete M_Car_Data[d];
		M_Car_Data.erase(M_Car_Data.begin() + d);
		d--;
	}

	return;
}
