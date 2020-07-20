#pragma once
#include<d3dx9.h>

class C_Float {
public:
	C_Float();
	C_Float(const float *s_Num);

	float Get(void) {
		return M_Float;
	}

	void Set(const float *s_Num) {
		M_Float = *s_Num;
	}
private:
	float M_Float;
};