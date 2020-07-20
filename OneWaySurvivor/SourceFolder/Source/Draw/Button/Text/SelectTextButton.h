#pragma once
#include<d3dx9.h>
#include"../Button2D.h"

class C_SelectTextButton :public C_Button2D
{
public:
	C_SelectTextButton(const D3DXVECTOR2 *Pos, const float s, const bool *PushFlg);
};