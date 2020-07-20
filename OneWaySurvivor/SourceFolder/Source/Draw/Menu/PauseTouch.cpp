#include "PauseTouch.h"
#include"../Button/Menu/PlayButton.h"
#include"../Button/Menu/SelectButton.h"

C_PauseTouch::C_PauseTouch()
{
	float y = 40.0f;

	D3DXVECTOR2 Pos = D3DXVECTOR2(wind.Base.Pos.x, wind.Base.Pos.y);
	m_button.push_back(new c_PlayButton(&Pos, -y));
	m_button.push_back(new c_SelectButton(&Pos, y));
}
