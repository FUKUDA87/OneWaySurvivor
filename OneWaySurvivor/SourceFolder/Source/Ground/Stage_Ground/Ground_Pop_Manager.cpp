#include "Ground_Pop_Manager.h"
#include"Ground_Type/Ground_Type_1.h"
#include"Ground_Type/Ground_Type_0.h"

C_Ground_Pop_Base * C_Ground_Pop_Manager::Get_Ground(const int *GroundNo)
{
	switch (*GroundNo)
	{
	case 0:
		return new C_Ground_Type_0();
		break;
	case 1:
		return new C_Ground_Type_1();
		break;
	default:
		return new C_Ground_Type_1();
		break;
	}

	return new C_Ground_Type_1();
}
