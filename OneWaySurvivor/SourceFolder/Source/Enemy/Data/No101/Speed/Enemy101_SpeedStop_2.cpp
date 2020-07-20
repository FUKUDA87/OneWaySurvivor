#include "Enemy101_SpeedStop_2.h"
#include"../../../../Move/Speed/Speed_Dead_A.h"
#include"Enemy101_Speed_3.h"

C_Speed_Update * C_Enemy101_SpeedStop_2::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//HP‚ªƒ[ƒ‚É‚È‚Á‚½Žž
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	switch (UpdateData->NowPhase)
	{
	case 1:
	case 3:
	case 5:
		return new C_Enemy101_Speed_3();
		break;
	}

	return nullptr;
}
