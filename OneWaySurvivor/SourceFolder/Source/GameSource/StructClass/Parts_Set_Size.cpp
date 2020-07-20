#include "Parts_Set_Size.h"

C_Parts_Set_Size::C_Parts_Set_Size(const int * TypeNo, const int * JointNo, const D3DXVECTOR3 * ScalPos)
{
	M_Size_Data.No.MeshTypeNo = *TypeNo;
	M_Size_Data.No.MeshJointNo = *JointNo;
	M_Size_Data.ScalPos = *ScalPos;
}
