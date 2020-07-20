#pragma once
#include<d3dx9.h>
#include"../Button2D.h"

class C_PlayTextButton :public C_Button2D
{
public:
	C_PlayTextButton(const D3DXVECTOR2 *Pos, const float s, const bool *PushFlg);
};