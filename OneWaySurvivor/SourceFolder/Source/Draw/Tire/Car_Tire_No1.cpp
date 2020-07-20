#include "Car_Tire_No1.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Car_Parts_Tire::C_Car_Parts_Tire(const S_CAR_PARTS_DATA * Data,C_Move_Parts_Base * Move):C_Car_Parts_Joint(Data)
{
	Draw_New(new C_Draw_Mesh_Base("Tire_1_Ver1.x"));
	New_Move(Move);
}
