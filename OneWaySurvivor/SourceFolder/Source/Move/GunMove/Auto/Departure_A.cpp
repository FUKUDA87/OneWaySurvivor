#include "Departure_A.h"

C_Departure_A::C_Departure_A(const int * Count):C_Departure_Gun_Auto_Base(Count)
{
}

void C_Departure_A::Update_NowCount(const int * Count)
{
	int i = 0;
	if (*Count > 0)i = 1;
	NowCount -= i;
}
