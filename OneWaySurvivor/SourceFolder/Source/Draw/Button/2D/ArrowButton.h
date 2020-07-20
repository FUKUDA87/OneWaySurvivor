#pragma once
#include<d3dx9.h>
#include"../Button2D.h"

class C_ArrowButton :public C_Button2D
{
public:
	C_ArrowButton(const D3DXVECTOR2 *Pos, const D3DXVECTOR2 *Scal,const bool ReverseFlg);
};