#include "Ground_Pop_Base.h"

C_Ground_Pop_Base::C_Ground_Pop_Base():M_Ground_PopNo(0)
{
	
}

C_Ground_Pop_Base::~C_Ground_Pop_Base()
{
	Delete_All_Ground_Pop();
}

S_GROUND_INIT_DATA C_Ground_Pop_Base::Get_Pop_Data(void)
{
	if (M_C_Data.size() < 1) Init_Data();

	if (M_C_Data.size() < 1) {
		C_Struct_Init Init;
		return Init.Get_S_GROUND_INIT_DATA(Co_Ground_Type_Straight);
	}

	return M_C_Data[M_Ground_PopNo]->Get_Data();
}

void C_Ground_Pop_Base::Ground_Pop_Rear(void)
{
	if (M_C_Data.size() < 1)return;

	if (M_C_Data[M_Ground_PopNo]->GroundNum_Count() != true) {
		delete M_C_Data[M_Ground_PopNo];
		M_C_Data.erase(M_C_Data.begin() + M_Ground_PopNo);
	}

	if (M_C_Data.size() < 1) {
		Init_Data();
	}
}

void C_Ground_Pop_Base::New_Data(const S_GROUND_INIT_DATA * Data, const int GroundNum)
{
	M_C_Data.push_back(new C_Ground_Pop_Data(Data, &GroundNum));
}

void C_Ground_Pop_Base::New_Data(const int * Grotype, const int GroundNum)
{
	C_Struct_Init Init;
	M_C_Data.push_back(new C_Ground_Pop_Data(&Init.Get_S_GROUND_INIT_DATA(*Grotype), &GroundNum));
}

void C_Ground_Pop_Base::Delete_All_Ground_Pop(void)
{
	if (M_C_Data.size() < 1)return;

	for (unsigned int d = 0; d < M_C_Data.size(); d++) {
		delete M_C_Data[d];
		M_C_Data.erase(M_C_Data.begin() + d);
		d--;
	}
}
