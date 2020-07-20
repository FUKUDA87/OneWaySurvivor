#pragma once
#include"../Struct.h"

class C_Parts_Set_Size {
public:
	C_Parts_Set_Size(const int *TypeNo, const int *JointNo, const D3DXVECTOR3* ScalPos);

	S_PARTS_SET_SIZE Get_Data(void) {
		return M_Size_Data;
	}
private:
	S_PARTS_SET_SIZE M_Size_Data;
};