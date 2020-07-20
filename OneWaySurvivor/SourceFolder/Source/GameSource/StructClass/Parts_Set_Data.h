#pragma once
#include<d3dx9.h>
#include"../Struct.h"

class C_Parts_Set_Data {
public:
	C_Parts_Set_Data(const int *TypeNo, const int *JointNo, const int *DrawNo);

	//ÉfÅ[É^ìnÇµ
	S_PARTS_SET_DATA Get_Data(void) {
		return M_Data;
	}
private:
	S_PARTS_SET_DATA M_Data;
};