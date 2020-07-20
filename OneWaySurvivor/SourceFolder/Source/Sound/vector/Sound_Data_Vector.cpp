#include "Sound_Data_Vector.h"
#include"../../GameSource/StructClass/Struct_Init.h"

C_Sound_Data_Vector::~C_Sound_Data_Vector()
{
	if (M_C_Data.size() < 1)return;

	for (unsigned int d = 0; d < M_C_Data.size(); d++) {
		delete M_C_Data[d];
		M_C_Data.erase(M_C_Data.begin() + d);
		d--;
	}
}

S_SOUND_DATA C_Sound_Data_Vector::Get_Sound_Data(const unsigned int *No)
{
	if((M_C_Data.size()<1)||(*No<0)||(*No>=M_C_Data.size()))return S_SOUND_DATA();

	return M_C_Data[*No]->Get_Data();
}

unsigned int C_Sound_Data_Vector::Get_Sound_Data_Num(void)
{
	return M_C_Data.size();
}

void C_Sound_Data_Vector::Delete_Sound(unsigned int * No)
{
	if ((M_C_Data.size() < 1) || (*No < 0) || (*No >= M_C_Data.size()))return;

	unsigned int d = *No;

	delete M_C_Data[d];
	M_C_Data.erase(M_C_Data.begin() + d);
	d--;

	*No = d;
}

void C_Sound_Data_Vector::New_Sound_Data(const S_SOUND_DATA * Set_Data)
{
	M_C_Data.push_back(new C_Sound_Data_Base(Set_Data));
}

void C_Sound_Data_Vector::New_Sound_Data(const int * Type, const int * Category, const int No, const int * Change)
{
	C_Struct_Init S_Init;
	New_Sound_Data(&S_Init.Get_S_SOUND_DATA(Type, Category, &No, Change));
}

void C_Sound_Data_Vector::New_Sound_Data(const int * Category, const int No, const D3DXVECTOR3 * Pos, const int * Change)
{
	C_Struct_Init S_Init;
	New_Sound_Data(&S_Init.Get_S_SOUND_DATA(&Co_Sound_Type_3D, Category, &No,Pos, Change));
}

void C_Sound_Data_Vector::New_Sound_Data_Change_No(const int * Type, const int * Category, const int No, const int * Change)
{
	int Cha = *Change;
	if (Cha > 0)Cha *= -1;
	New_Sound_Data(Type, Category, No, &Cha);
}

void C_Sound_Data_Vector::Change_Menu_All(void)
{
	if (M_C_Data.size() < 1)return;

	for (auto && d : M_C_Data) {
		d->Change_Menu();
	}
}
