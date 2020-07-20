#include "Stage_D1_1.h"
#include"Stage_D1_2.h"

C_Stage_D1_1::C_Stage_D1_1()
{
	New_Car_Data(co_EnemyCar, 1, 0, -5, 2);
}

C_Car_Pop_Base * C_Stage_D1_1::Next_Pop(void)
{
	return new C_Stage_D1_2();
}
