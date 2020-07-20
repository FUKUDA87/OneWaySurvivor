#include "Stand_DrawManager.h"
#include"Stand_No0.h"
#include"../../Move/Parts/StopMove.h"
#include"Stand_No101.h"

C_Car_Parts_Joint * C_Stand_DrawManager::Get_Draw(const int * StandNo, const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move)
{
	switch (*StandNo)
	{
	case 0:
		return new C_Stand_No0(Data,Move);
		break;
	case 1:
		return new C_Stand_No1(Data,Move);
		break;
	case 101:
		return new C_Stand_No101(Data, Move);
		break;
	default:
		return new C_Stand_No1(Data,Move);
		break;
	}

	return new C_Stand_No1(Data,Move);
}

C_Car_Parts_Joint * C_Stand_DrawManager::Get_Draw_Stop(const int * StandNo, const S_CAR_PARTS_DATA * Data)
{
	return Get_Draw(StandNo,Data,new C_StopMove());
}
