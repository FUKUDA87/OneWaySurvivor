#include "Departure_Gun_Auto_Base.h"

C_Departure_Gun_Auto_Base::C_Departure_Gun_Auto_Base(const int * Count)
{
	NowCount = *Count;
}

bool C_Departure_Gun_Auto_Base::Get_BulletFlg(const int * Count)
{
	Update_NowCount(Count);

	if (NowCount < 0) {
		NowCount = 0;
		return false;
	}

	bool Flg = true;

	if (NowCount <= 0)Flg = false;

	return Flg;
}

void C_Departure_Gun_Auto_Base::Update_NowCount(const int * Count)
{
	NowCount -= *Count;
}
