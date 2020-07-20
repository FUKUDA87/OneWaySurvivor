#include "OverTouch.h"
#include"../Button/Menu/RetryButton.h"
#include"../Button/Menu/SelectButton.h"

C_OverTouch::C_OverTouch()
{
	float y = 40.0f;

	D3DXVECTOR2 Pos = D3DXVECTOR2(wind.Base.Pos.x, wind.Base.Pos.y);
	m_button.push_back(new c_RetryButton(&Pos, -y));
	m_button.push_back(new c_SelectButton(&Pos, y));
}
