#include "Speed_Stop_A.h"
#include"Speed_Dead_A.h"
#include"../../Enemy/Data/No1/Speed/SpeedUp.h"

C_Speed_Update * C_Speed_Stop_A::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//車のHpがゼロの場合
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//動けるようになった
	if (UpdateData->UpdateStopFlg != true)return new SpeedUp1();

	return nullptr;
}
