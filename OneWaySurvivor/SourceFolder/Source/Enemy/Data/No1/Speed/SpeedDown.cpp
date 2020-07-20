#include "SpeedDown.h"
#include"SpeedUp.h"
#include"../../../../Move/Speed/Speed_Dead_A.h"
#include"../../../../Move/Speed/Speed_Stop_A.h"

SpeedDown1::SpeedDown1()
{
	SpeedDownNum = -1;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

C_Speed_Update * SpeedDown1::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//車のHpがゼロの場合
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (UpdateData->UpdateStopFlg == true)return new C_Speed_Stop_A();

	//ターゲットの後ろ過ぎた場合
	if (UpdateData->NowGroNo < UpdateData->TargetGroNo - 3)return new SpeedUp1();

	if (CountUpdate() == false) {
		*Now_Speed += SpeedDownNum;
		if (*Now_Speed < UpdateData->TargetSpeed - 5) *Now_Speed = UpdateData->TargetSpeed - 5;
	}
	if (UpdateData->NowGroNo < UpdateData->TargetGroNo) return new SpeedUp2();

	return nullptr;
}

//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※

SpeedDown2::SpeedDown2()
{
	SpeedDownNum = -2;
	CountDown = rand() % 20 + 20;
}

C_Speed_Update * SpeedDown2::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//車のHpがゼロの場合
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (UpdateData->UpdateStopFlg == true)return new C_Speed_Stop_A();

	//ターゲットの後ろ過ぎた場合
	if (UpdateData->NowGroNo < UpdateData->TargetGroNo - 3)return new SpeedUp1();

	if (UpdateData->NowGroNo < UpdateData->TargetGroNo) return new SpeedUp2();

	if (CountUpdate() == true)return nullptr;

	*Now_Speed += SpeedDownNum;

	if (*Now_Speed < UpdateData->TargetSpeed - 5) *Now_Speed = UpdateData->TargetSpeed - 5;

	return nullptr;
}