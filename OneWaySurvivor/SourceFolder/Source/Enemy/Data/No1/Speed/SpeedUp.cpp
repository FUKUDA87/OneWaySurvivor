#include "SpeedUp.h"
#include"SpeedDown.h"
#include"../../../../Move/Speed/Speed_Dead_A.h"
#include"../../../../Move/Speed/Speed_Stop_A.h"

SpeedUp1::SpeedUp1()
{
	SpeedUpNum = 2;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

C_Speed_Update * SpeedUp1::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//車のHpがゼロの場合
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (UpdateData->UpdateStopFlg == true)return new C_Speed_Stop_A();

	if (UpdateData->NowGroNo >= UpdateData->TargetGroNo) return new SpeedDown1();

	if (CountUpdate() == true) return nullptr;

	*Now_Speed += SpeedUpNum;

	if (*Now_Speed > UpdateData->TargetSpeed + 20) *Now_Speed = UpdateData->TargetSpeed + 20;

	return nullptr;
}

//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※

SpeedUp2::SpeedUp2()
{
	SpeedUpNum = 1;
	CountDown = rand() % 20 + 20;
}

C_Speed_Update * SpeedUp2::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//車のHpがゼロの場合
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (UpdateData->UpdateStopFlg == true)return new C_Speed_Stop_A();

	//ターゲットの後ろ過ぎた場合
	if (UpdateData->NowGroNo < UpdateData->TargetGroNo - 3)return new SpeedUp1();

	if (UpdateData->NowGroNo > UpdateData->TargetGroNo) return new SpeedDown2();

	if (CountUpdate() == true) return nullptr;
	*Now_Speed += SpeedUpNum;
	if (*Now_Speed > UpdateData->TargetSpeed + 5) *Now_Speed = UpdateData->TargetSpeed + 5;
	return nullptr;
}
