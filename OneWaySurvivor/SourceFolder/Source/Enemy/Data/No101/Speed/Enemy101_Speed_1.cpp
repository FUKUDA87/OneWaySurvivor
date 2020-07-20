#include "Enemy101_Speed_1.h"
#include"../../../../Move/Speed/Speed_Dead_A.h"
#include"Enemy101_SpeedStop_1.h"

C_Speed_Update * C_Enemy101_Speed_1::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//HPがゼロになった時
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//ターゲットの前に移動した時
	if (UpdateData->NowGroNo > UpdateData->TargetGroNo - 1) {

		//ターゲットと同じにする
		*Now_Speed = UpdateData->TargetSpeed;

		//次の動きに移動する
		return new C_Enemy101_SpeedStop_1();
	}
	if (CountUpdate() == true) return nullptr;
	*Now_Speed += SpeedUpNum;
	if (*Now_Speed > UpdateData->TargetSpeed + 25) *Now_Speed = UpdateData->TargetSpeed + 25;

	return nullptr;
}
