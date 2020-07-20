#include "Gun_Parts_Category.h"

C_Gun_Parts_Category::C_Gun_Parts_Category(const int * set_CategoryNo)
{
	Init_C_Gun_Parts_Category();
	Set_CategoryNo(set_CategoryNo);
}

bool C_Gun_Parts_Category::Update(void)
{
	NowRate--;
	if (NowRate < 0)NowRate = 0;

	Judg_MoveFlg();

	return true;
}

bool C_Gun_Parts_Category::Get_Bullet_Shot_Flg(void)
{
	if (Get_NowRate() > 0)return false;

	if (Get_MoveFlg() == 1)return false;

	if (Get_TriggerFlg() != true)return false;

	return true;
}

void C_Gun_Parts_Category::Init_C_Gun_Parts_Category(void)
{
	NowRate = 0;
	MoveFlg = 0;
	Move_f = 0.0f;
	TriggerFlg = false;
}

void C_Gun_Parts_Category::Judg_MoveFlg(void)
{
	if (Move_f < 0.0f) {
		Set_MoveFlg(0);
		Move_f = 0.0f;
		return;
	}

	if (Move_f > 0.0f) {
		Set_MoveFlg(1);

		if (Move_f > 1.0f) {
			Set_MoveFlg(2);
			Move_f = 1.0f;
			return;
		}
	}
}
