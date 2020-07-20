#include "Car_Parts_Joint.h"

C_Car_Parts_Joint::C_Car_Parts_Joint(const S_CAR_PARTS_DATA * set_Data):C_Car_Parts_Base(set_Data)
{

}

C_Car_Parts_Joint::~C_Car_Parts_Joint()
{
	Delete_ALL_Juint_Data();
}

void C_Car_Parts_Joint::Delete_ALL_Juint_Data(void)
{
	if (M_Joint_Data.size() < 1)return;

	for (unsigned int d = 0; d < M_Joint_Data.size(); d++) {
		delete M_Joint_Data[d];
		M_Joint_Data.erase(M_Joint_Data.begin() + d);
		d--;
	}
}

void C_Car_Parts_Joint::New_Joint_Data(const S_CAR_PARTS_DATA * Data)
{
	M_Joint_Data.push_back(new S_CAR_PARTS_DATA);
	*M_Joint_Data[M_Joint_Data.size() - 1] = *Data;
}

