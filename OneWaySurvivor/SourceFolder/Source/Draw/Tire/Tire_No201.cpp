#include "Tire_No201.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Tire_No201::C_Tire_No201(const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move) :C_Car_Parts_Joint(Data)
{
	Draw_New(new C_Draw_Mesh_Base("CarTire1-3-1.x"));
	New_Move(Move);
}
