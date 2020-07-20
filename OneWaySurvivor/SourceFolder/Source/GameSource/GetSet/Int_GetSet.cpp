#include "Int_GetSet.h"

C_Int::C_Int()
{
	int i = 0;
	Set(&i);
}

C_Int::C_Int(const int * s_Num)
{
	Set(s_Num);
}
