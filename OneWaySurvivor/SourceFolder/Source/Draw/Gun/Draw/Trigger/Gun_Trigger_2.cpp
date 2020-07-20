#include "Gun_Trigger_2.h"

C_Gun_Trigger_2::C_Gun_Trigger_2()
{
	Init();
}

void C_Gun_Trigger_2::Trigger(std::vector<C_Gun_Parts_Category*> Category, const bool * TriggerFlg)
{
	if (Category.size() < 1)return;

	if (MouthNo < 0)MouthNo = 0;

	if (MouthNo >= Category.size())MouthNo = 0;

	Category[MouthNo]->Set_TriggerFlg(TriggerFlg);
}

void C_Gun_Trigger_2::Gun_Mouth_Change(void)
{
	MouthNo++;
}

void C_Gun_Trigger_2::Init(void)
{
	MouthNo = 0;
}
