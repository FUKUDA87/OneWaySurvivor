#include "EnemySelect.h"
#include"../GameSource/Const.h"
#include"EnemyNoConst.h"

BODYDATACar C_EnemySelect::GetEnemy(const int EnemyNo)
{
	//åüçı
	if (GetEnemyJudg(EnemyNo) == false) {
		//åüçıé∏îs
		eData.Body.CarBodyNo = CarNo101;
		eData.Body.TireNo = TireNo101;
		eData.Body.StandNo = StandNo101;
		eData.Body.GunNo = 1;
	}
	return eData;
}

bool C_EnemySelect::GetEnemyJudg(const int EnemyNo)
{
	if (GetEnemy1(EnemyNo) == true)return true;
	if (GetEnemyBoss1(EnemyNo) == true)return true;
	return false;
}

bool C_EnemySelect::GetEnemy1(const int EnemyNo)
{
	if (EnemyNo != EnemyNo1)return false;
	eData.Body.CarBodyNo = CarNo101;
	eData.Body.TireNo = TireNo101;
	eData.Body.StandNo = StandNo101;
	eData.Body.GunNo = 1;
	eData.ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	eData.MaxHp = 40;
	return true;
}

bool C_EnemySelect::GetEnemyBoss1(const int EnemyNo)
{
	if (EnemyNo != EnemyBossNo101)return false;
	eData.Body.CarBodyNo = CarNo201;
	eData.Body.TireNo = TireNo201;
	eData.Body.StandNo = StandNo101;
	eData.Body.GunNo = 1;
	eData.ScalPos = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	eData.MaxHp = 100;
	return true;
}
