#include "OptionButton.h"
#include"../Text/OptionTextButton.h"
#include"../2D/WindowButton.h"

C_OptionButton::C_OptionButton()
{
	float Size = 0.7f;

	button2D.push_back(new C_WindowButton());
	D3DXVECTOR2 sp = D3DXVECTOR2(0.23f, 0.13f)*Size;
	button2D[button2D.size() - 1]->setScalSize(&sp);

	button2D.push_back(new C_OptionTextButton());
	float ss = 1.0f*Size;
	button2D[button2D.size() - 1]->setScalSize(&ss);

	pos.x = 1280.0f * 0.9f;
	pos.y = 60.0f;
}
