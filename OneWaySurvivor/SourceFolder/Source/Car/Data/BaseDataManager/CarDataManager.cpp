#include "CarDataManager.h"

int C_CarDataManager::GetDrawNum(int CarNo, bool SaveFlg)
{
	if (SaveFlg == true)LoadSaveDN(CarNo);
	return LoadDN(CarNo);
}

S_CAR_PARTS_DATA C_CarDataManager::GetDrawSet(int CarNo, const int * DrawNo, bool SaveFlg)
{
	if (SaveFlg == true)LoadSave_Car_Parts_Data(CarNo,DrawNo);
	return Load_Car_Parts_Data(CarNo,DrawNo);
}

bool C_CarDataManager::DrawNumJudg(int CarNo)
{
	return false;
}

bool C_CarDataManager::DrawSetJudg(int CarNo, const int * DrawNo)
{
	return false;
}

