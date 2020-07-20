#include "Gun_Trigger_1.h"

void C_Gun_Trigger_1::Trigger(std::vector<C_Gun_Parts_Category*> Category, const bool * TriggerFlg)
{
	if (Category.size() < 1)return;

	for (auto && g:Category) {
		g->Set_TriggerFlg(TriggerFlg);
	}
}

void C_Gun_Trigger_1::Gun_Mouth_Change(void)
{
}
