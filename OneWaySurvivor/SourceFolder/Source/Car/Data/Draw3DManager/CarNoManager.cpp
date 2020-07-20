#include "CarNoManager.h"

int C_CarNoManager::GetNextNo(const int * NowNo)
{
	if (*NowNo == CarNo1)return CarNo2;
	if (*NowNo == CarNo2)return CarNo101;
	if (*NowNo == CarNo101)return CarNo201;

	return CarNo1;
}
