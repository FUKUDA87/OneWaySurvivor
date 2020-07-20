#include "GunMoveBase_A.h"
#include"../../../../Move/GunMove/Auto/Departure_A.h"
#include"../../../../Move/GunMove/Auto/Departure_B.h"

C_Departure_Gun_Auto_Base * C_GunMoveBase_A::Get_Departure(const S_BULLET_DEPAR * Data)
{
	if (Data->Bullet_Gun_Mode == 1)return new C_Departure_Gun_Auto_Base(&Data->Count_Departure);
	if (Data->Bullet_Gun_Mode == 2)return new C_Departure_A(&Data->Count_Departure);
	if (Data->Bullet_Gun_Mode == 3)return new C_Departure_B(&Data->Count_Departure);

	int i = 0;
	return new C_Departure_Gun_Auto_Base(&i);
}
