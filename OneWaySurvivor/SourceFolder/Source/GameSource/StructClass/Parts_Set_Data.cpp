#include "Parts_Set_Data.h"

C_Parts_Set_Data::C_Parts_Set_Data(const int *TypeNo, const int *JointNo, const int *DrawNo)
{
	M_Data.MeshTypeNo = *TypeNo;
	M_Data.MeshJointNo = *JointNo;
	M_Data.DrawNo = *DrawNo;
}
