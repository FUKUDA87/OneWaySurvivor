#include "Car_Pop_New.h"
#include"Car_Pop_Manager.h"

C_Car_Pop_New::C_Car_Pop_New(const int * StageNo)
{
	C_Car_Pop_Manager Manager;

	M_C_Car_Pop_Base = Manager.Get_Pop(StageNo);

	Change_Class_EndFlg = false;
}

C_Car_Pop_New::~C_Car_Pop_New()
{
	if (M_C_Car_Pop_Base != nullptr) {
		delete M_C_Car_Pop_Base;
	}
}

bool C_Car_Pop_New::Update(const bool * MoveFlg)
{
	if (M_C_Car_Pop_Base == nullptr)return false;

	Change_Class_EndFlg = false;

	C_Car_Pop_Base* L_Base;

	L_Base = M_C_Car_Pop_Base->Update(MoveFlg);
	if (L_Base != nullptr) {
		delete M_C_Car_Pop_Base;
		M_C_Car_Pop_Base = L_Base;

		Change_Class_EndFlg = true;
	}

	return true;
}

S_CAR_INIT_DATA C_Car_Pop_New::Get_Next_Car_Data_N(void)
{
	if (M_C_Car_Pop_Base == nullptr) return S_CAR_INIT_DATA();

	return M_C_Car_Pop_Base->Get_Next_Car_Data();
}

S_NOW_WAVE_DATA C_Car_Pop_New::Get_Now_Wave_Data_N(void)
{
	if (M_C_Car_Pop_Base == nullptr)return S_NOW_WAVE_DATA();

	return M_C_Car_Pop_Base->Get_Stage_Phase_Data();
}

bool C_Car_Pop_New::Get_Car_Pop_Flg_N(void)
{
	if (M_C_Car_Pop_Base == nullptr) return false;

	return M_C_Car_Pop_Base->Get_Car_Pop_Flg();
}

void C_Car_Pop_New::Car_Init_Rear_N(void)
{
	if (M_C_Car_Pop_Base == nullptr) return;

	M_C_Car_Pop_Base->Car_Init_Rear();
}

void C_Car_Pop_New::Set_Now_Enemy_Num_N(const int * Enemy_Num)
{
	if (M_C_Car_Pop_Base == nullptr) return;

	M_C_Car_Pop_Base->Set_Now_Enemy_Num(Enemy_Num);
}

int C_Car_Pop_New::Get_GroundNo(void)
{
	if (M_C_Car_Pop_Base == nullptr)return 0;

	return M_C_Car_Pop_Base->Get_GroundNo();
}

void C_Car_Pop_New::M_Car_Pop_Update_N(std::vector<C_EnemyAi*> enemy)
{
	if (M_C_Car_Pop_Base == nullptr)return;

	M_C_Car_Pop_Base->M_Car_Pop_Update(enemy);
}