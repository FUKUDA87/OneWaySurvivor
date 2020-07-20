#include "Tire_No101.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Tire_No101::C_Tire_No101(const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move) :C_Car_Parts_Joint(Data)
{
	Draw_New(new C_Draw_Mesh_Base("tire2-2.x"));
	New_Move(Move);
}
