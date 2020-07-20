#include "ButtonBase.h"

C_ButtonBase::~C_ButtonBase()
{
	Delete();
}

void C_ButtonBase::Draw2D(void)
{
	if (button2D.size() <= 0)return;

	for (auto && b : button2D)b->Draw2D();
}

bool C_ButtonBase::Update(const D3DXVECTOR2 * Pos)
{
	if (button2D.size() <= 0)return false;

	if (Pos != nullptr)pos = *Pos;

	for (auto && b : button2D)b->Update(&pos);

	return true;
}

bool C_ButtonBase::TouchJudg(void)
{
	if (button2D.size() <= 0)return false;

	return button2D[0]->TouchJudg();
}

void C_ButtonBase::Delete(void)
{
	if (button2D.size() <= 0)return;

	for (unsigned int bc = 0; bc < button2D.size(); bc++)
	{
		delete button2D[bc];
		button2D.erase(button2D.begin() + bc);
		bc--;
	}
}
