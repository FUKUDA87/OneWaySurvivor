#include "SpeedDeadStop.h"

c_SpeedDeadStop::c_SpeedDeadStop()
{
	InitFlg = true;
}

C_Speed_Update * c_SpeedDeadStop::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	if (InitFlg == true) {
		InitFlg = false;
		*Now_Speed = 0;
	}

	return nullptr;
}
