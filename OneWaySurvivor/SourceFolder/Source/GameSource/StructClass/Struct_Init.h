#pragma once
#include<d3dx9.h>
#include"../Struct.h"

class C_Struct_Init {
public:
	//ínñ ÇÃèâä˙âªèÓïÒ
	S_GROUND_INIT_DATA Get_S_GROUND_INIT_DATA(const int gType, const float Ang, const float Length, const bool LengthAuto);
	S_GROUND_INIT_DATA Get_S_GROUND_INIT_DATA(const int gType);
	S_SOUND_DATA Get_S_SOUND_DATA(const int *Type, const int *Category, const int *No, const int *Change);
	S_SOUND_DATA Get_S_SOUND_DATA(const int *Type, const int *Category, const int *No,const D3DXVECTOR3* Pos, const int *Change);
};