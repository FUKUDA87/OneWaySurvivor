#include "Enemy101_SpeedStop_1.h"
#include"../../../../Move/Speed/Speed_Dead_A.h"
#include"Enemy101_Speed_2.h"

C_Speed_Update * C_Enemy101_SpeedStop_1::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//HP‚ªƒ[ƒ‚É‚È‚Á‚½Žž
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	switch (UpdateData->NowPhase)
	{
	case 2:
	case 4:
	case 6:
		return new C_Enemy101_Speed_2();
		break;
	}

	return nullptr;
}
