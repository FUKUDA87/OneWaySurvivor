#include "Door_No1.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Door_No1::C_Door_No1(const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move) :C_Car_Parts_Joint(Data)
{
	if (Data->MeshJointNo > 0) {
		Draw_New(new C_Draw_Mesh_Base("CarDoorA1-3-1.x"));
	}
	else {
		Draw_New(new C_Draw_Mesh_Base("CarDoorB1-3-1.x"));
	}
	New_Move(Move);
}
