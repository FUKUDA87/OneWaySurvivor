#include "Car_Pop_Update_1.h"

C_Car_Pop_Base * C_Car_Pop_Update_1::Update(const bool * Update_MoveFlg)
{
	if (*Update_MoveFlg != true) {
		M_Car_Pop_Flg = false;
		return nullptr;
	}

	if ((Get_Pop_Data_Num() < 1) && (Get_Stage_Phase_Data().Enemy_Alive_Num < 1)) M_Car_Pop_EndFlg = true;

	if (M_Car_Pop_EndFlg == true) {
		return Next_Pop();
	}

	Update_Car_Count();

	return nullptr;
}

C_Car_Pop_Base * C_Car_Pop_Update_1::Next_Pop(void)
{
	return nullptr;
}

void C_Car_Pop_Update_1::New_All_Pop(void)
{
}
