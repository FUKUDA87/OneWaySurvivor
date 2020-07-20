#include "Struct_Init.h"
#include"../../Const/Const_Ground_Type.h"

S_GROUND_INIT_DATA C_Struct_Init::Get_S_GROUND_INIT_DATA(const int gType, const float Ang, const float Length, const bool LengthAuto)
{
	S_GROUND_INIT_DATA Data;

	Data.gType = gType;
	Data.Ang = Ang;
	Data.Length = Length;
	Data.LengthAuto = LengthAuto;

	return Data;
}

S_GROUND_INIT_DATA C_Struct_Init::Get_S_GROUND_INIT_DATA(const int gType)
{
	if (gType != Co_Ground_Type_Straight) {
		return Get_S_GROUND_INIT_DATA(gType, 90.0f / 5.0f, 5.0f, false);
	}
	
	return Get_S_GROUND_INIT_DATA(gType, 0.0f, 0.0f, true);
}

S_SOUND_DATA C_Struct_Init::Get_S_SOUND_DATA(const int * Type, const int * Category, const int *No, const int * Change)
{
	S_SOUND_DATA Data;
	Data.Sound_Type = *Type;
	Data.Sound_CategoryNo = *Category;
	Data.Sound_No = *No;
	Data.Change_Type = *Change;
	return Data;
}

S_SOUND_DATA C_Struct_Init::Get_S_SOUND_DATA(const int * Type, const int * Category, const int * No, const D3DXVECTOR3 * Pos, const int * Change)
{
	S_SOUND_DATA Data = Get_S_SOUND_DATA(Type, Category, No, Change);
	Data.Pos = *Pos;
	return Data;
}
