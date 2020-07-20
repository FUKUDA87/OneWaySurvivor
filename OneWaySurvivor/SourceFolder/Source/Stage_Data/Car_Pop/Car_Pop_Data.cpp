#include "Car_Pop_Data.h"

C_Car_Pop_Data::C_Car_Pop_Data(const S_CAR_INIT_DATA * Data, const int * Count)
{
	M_Count = *Count;

	M_Data = *Data;
}

bool C_Car_Pop_Data::Update_Count(void)
{
	M_Count--;

	if (M_Count < 0) {
		M_Count = 0;
		return true;
	}

	return false;
}
