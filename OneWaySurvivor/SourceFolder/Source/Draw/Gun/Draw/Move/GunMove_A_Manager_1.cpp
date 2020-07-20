#include "GunMove_A_Manager_1.h"

#include"GunManual_1_1.h"
#include"GunStopMove_1.h"

C_GunMoveBase_A * C_GunMove_A_Manager_1::Get_GunMove_A(const int * MoveNo)
{
	if (*MoveNo == 0)return new C_GunStopMove_1();

	if (*MoveNo == 1)return new C_GunManual_1_1();

	return new C_GunStopMove_1();
}
