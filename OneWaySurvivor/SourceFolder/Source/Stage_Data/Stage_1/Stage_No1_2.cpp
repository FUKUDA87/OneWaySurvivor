#include "Stage_No1_2.h"
#include"Stage_No1_3.h"

C_Stage_No1_2::C_Stage_No1_2()
{
	New_Car_Data(co_EnemyCar, 1, 0, -10);
	New_Car_Data(co_EnemyCar, 1, 180, -10);
	New_Car_Data(co_EnemyCar, 1, 360, -10);
	New_Car_Data(co_EnemyCar, 1, 100, -10);
	New_Car_Data(co_EnemyCar, 1, 180, -10);

	//¶¬‚³‚ê‚é’n–Ê‚Ì‰Šú‰»
	M_Ground_Type = 1;
}


C_Car_Pop_Base * C_Stage_No1_2::Next_Pop(void)
{
	
	return new C_Stage_No1_3();
}
