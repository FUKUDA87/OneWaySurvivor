#pragma once
#include<d3dx9.h>
#include"../Button2D.h"

class C_RetryTextButton :public C_Button2D
{
public:
	C_RetryTextButton(const D3DXVECTOR2 *Pos, const float s, const bool *PushFlg);
};