#include "float_GetSet.h"

C_Float::C_Float()
{
	float f = 0.0f;
	Set(&f);
}

C_Float::C_Float(const float * s_Num)
{
	Set(s_Num);
}
