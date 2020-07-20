#include "Ground_Pop_New.h"
#include"Ground_Type/Ground_Type_1.h"
#include"Ground_Pop_Manager.h"

C_Ground_Pop_New::C_Ground_Pop_New()
{
	Init();
	New_Pop(new C_Ground_Type_1());
}

C_Ground_Pop_New::C_Ground_Pop_New(const int GroundNo)
{
	New_Pop(&GroundNo);
}

C_Ground_Pop_New::C_Ground_Pop_New(C_Ground_Pop_Base * Pop)
{
	Init();
	New_Pop(Pop);
}

C_Ground_Pop_New::~C_Ground_Pop_New()
{
	Delete_C_Ground_Pop();
}

S_GROUND_INIT_DATA C_Ground_Pop_New::Get_Pop_Data_N(void)
{
	if (M_C_Ground_Pop == nullptr) {
		C_Struct_Init Init;
		return Init.Get_S_GROUND_INIT_DATA(Co_Ground_Type_Straight);
	}

	return M_C_Ground_Pop->Get_Pop_Data();
}

void C_Ground_Pop_New::Ground_Pop_Rear_N(void)
{
	if (M_C_Ground_Pop == nullptr)return;

	M_C_Ground_Pop->Ground_Pop_Rear();
}

void C_Ground_Pop_New::New_Pop(C_Ground_Pop_Base * Pop)
{
	Delete_C_Ground_Pop();

	M_C_Ground_Pop = Pop;
}

void C_Ground_Pop_New::New_Pop(const int * GroundNo)
{
	C_Ground_Pop_Manager Manager;

	M_GroundNo = *GroundNo;

	New_Pop(Manager.Get_Ground(&M_GroundNo));
}

void C_Ground_Pop_New::Delete_C_Ground_Pop(void)
{
	if (M_C_Ground_Pop == nullptr)return;

	delete M_C_Ground_Pop;
}

void C_Ground_Pop_New::Init(void)
{
	M_GroundNo = 0;
}
