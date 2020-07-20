#include "Car_Parts_Judg_Mesh.h"
#include"../../Move/Parts/StopMove.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Car_Parts_Judg_Mesh::C_Car_Parts_Judg_Mesh(const S_CAR_PARTS_DATA * Data, std::string FileName):C_Car_Parts_Joint(Data)
{
	New_Move(new C_StopMove());
	Draw_New(new C_Draw_Mesh_Base(FileName));
	Draw_Flg = false;
}
