#include "Tire_DrawManager.h"
#include"../../Move/Parts/StopMove.h"
#include"../../Move/Parts/TireMove_No1.h"
#include"Tire_No101.h"
#include"Tire_No201.h"

C_Car_Parts_Joint * C_Tire_DrawManager::Get_Draw_Stop(const int * TireNo, const S_CAR_PARTS_DATA * Data)
{
	return Get_Draw(TireNo,Data,new C_StopMove());
}

C_Car_Parts_Joint * C_Tire_DrawManager::Get_Draw_Tire(const int * TireNo, const S_CAR_PARTS_DATA * Data)
{
	return Get_Draw(TireNo, Data, new C_TireMove_No1());
}

C_Car_Parts_Joint * C_Tire_DrawManager::Get_Draw(const int * TireNo, const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base * Move)
{
	if (*TireNo == 1)return new C_Car_Parts_Tire(Data,Move);
	if (*TireNo == 101)return new C_Tire_No101(Data, Move);
	if (*TireNo == 201)return new C_Tire_No201(Data, Move);



	return new C_Car_Parts_Tire(Data, Move);
}
