#include "Speed_Dead_A.h"
#include"SpeedDeadStop.h"

Speed_Dead_A::Speed_Dead_A()
{
	Count_Now = Count_Start = 20;
	InitFlg = true;
}

C_Speed_Update * Speed_Dead_A::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	if (InitFlg == true) {

		InitFlg = false;

		if (*Now_Speed > UpdateData->TargetSpeed)*Now_Speed = UpdateData->TargetSpeed;

	}

	Count_Now--;

	if (Count_Now > 0)return nullptr;

	Count_Now = Count_Start;

	*Now_Speed -= 1;

	if (*Now_Speed < 0) {
		*Now_Speed = 0;
		return new c_SpeedDeadStop();
	}

	return nullptr;
}


