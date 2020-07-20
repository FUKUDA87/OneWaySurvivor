#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Car_Pop_Data {
public:
	C_Car_Pop_Data(const S_CAR_INIT_DATA *Data,const int *Count);

	bool Update_Count(void);

	//î•ñ“n‚µ
	S_CAR_INIT_DATA Get_Data(void) {
		return M_Data;
	}
private:
	S_CAR_INIT_DATA M_Data;

	int M_Count;
};