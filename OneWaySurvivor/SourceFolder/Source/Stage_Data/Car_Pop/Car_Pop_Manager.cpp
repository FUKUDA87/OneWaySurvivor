#include "Car_Pop_Manager.h"
#include"../Stage_1/Stage_No1_1.h"
#include"../../Const/Const_Stage_Type.h"
#include"../Stage_D1/Stage_D1_1.h"

C_Car_Pop_Base * C_Car_Pop_Manager::Get_Pop(const int * StageNo)
{
	switch (*StageNo)
	{
	case 1:
		return new C_Stage_No1_1();
		break;
	case Co_Stage_Type_Debug:
		return new C_Stage_D1_1();
		break;
	default:
		return new C_Stage_No1_1();
		break;
	}
	return new C_Stage_No1_1();
}
