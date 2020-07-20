#pragma once
#include<d3dx9.h>

class C_Int {
public:
	C_Int();
	C_Int(const int *s_Num);

	int Get(void) {
		return M_Int;
	}

	void Set(const int *s_Num) {
		M_Int = *s_Num;
	}
private:
	int M_Int;
};