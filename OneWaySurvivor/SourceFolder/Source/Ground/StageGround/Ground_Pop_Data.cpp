#include "Ground_Pop_Data.h"

C_Ground_Pop_Data::C_Ground_Pop_Data(const S_GROUND_INIT_DATA * Data, const int * GroundNum)
{
	M_GroundNum = *GroundNum;

	M_S_Data = *Data;
}

bool C_Ground_Pop_Data::GroundNum_Count(void)
{
	M_GroundNum--;

	if (M_GroundNum < 0) M_GroundNum = 0;

	if (M_GroundNum == 0) return false;

	return true;
}
