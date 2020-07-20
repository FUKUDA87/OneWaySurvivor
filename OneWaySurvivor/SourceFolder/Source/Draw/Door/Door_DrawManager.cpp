#include "Door_DrawManager.h"
#include"../../Move/Parts/StopMove.h"
#include"../../Move/Parts/Door_Move_1.h"

C_Car_Parts_Joint * C_Door_DrawManager::Get_Draw(const int * DoorNo, const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move)
{
	if (*DoorNo == 1)return new C_Door_No1(Data, Move);


	return new C_Door_No1(Data, Move);
}

C_Car_Parts_Joint * C_Door_DrawManager::Get_Draw_Stop(const int * DoorNo, const S_CAR_PARTS_DATA * Data)
{
	return Get_Draw(DoorNo,Data, new C_StopMove());
}

C_Car_Parts_Joint * C_Door_DrawManager::Get_Draw_Door(const int * DoorNo, const S_CAR_PARTS_DATA * Data, const float *MoveAng)
{
	float Ang = *MoveAng;
	if (Data->MeshJointNo < 0)Ang *= -1.0f;
	float Anime = 0.0f,Frame=0.1f;
	return Get_Draw(DoorNo, Data, new C_Door_Move_1(&Ang,&Frame,&Anime));


}
