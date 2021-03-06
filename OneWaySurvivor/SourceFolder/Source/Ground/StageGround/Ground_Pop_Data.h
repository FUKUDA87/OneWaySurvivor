#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Ground_Pop_Data {
public:
	C_Ground_Pop_Data(const S_GROUND_INIT_DATA* Data, const int *GroundNum);

	//地面数の削除
	bool GroundNum_Count(void);

	//地面の情報渡し
	S_GROUND_INIT_DATA Get_Data(void) {
		return M_S_Data;
	}
protected:

private:
	S_GROUND_INIT_DATA M_S_Data;

	int M_GroundNum;
};