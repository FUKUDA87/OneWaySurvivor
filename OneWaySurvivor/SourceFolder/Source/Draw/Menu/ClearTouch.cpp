#include "ClearTouch.h"
#include"../Button/Menu/TitleButton.h"
#include"../Button/Menu/SelectButton.h"

C_ClearTouch::C_ClearTouch()
{
	float y = 40.0f;

	D3DXVECTOR2 Pos = D3DXVECTOR2(wind.Base.Pos.x, wind.Base.Pos.y);
	m_button.push_back(new c_SelectButton(&Pos, -y));
	m_button.push_back(new c_TitleButton(&Pos, y));
}
