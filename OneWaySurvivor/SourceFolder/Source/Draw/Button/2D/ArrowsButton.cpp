#include "ArrowsButton.h"
#include"ArrowButton.h"

C_ArrowsButton::C_ArrowsButton(const D3DXVECTOR2 * Pos, const D3DXVECTOR2 * scalSize, const float * TransX)
{
	pos = *Pos;

	transX = *TransX;
	if (transX > 0.0f)transX *= -1.0f;

	

	D3DXVECTOR2 p = *Pos;
	p.x += transX;
	button2D.push_back(new C_ArrowButton(&p, scalSize, false));
	p = *Pos;
	p.x += transX * -1.0f;
	button2D.push_back(new C_ArrowButton(&p, scalSize, true));
}

bool C_ArrowsButton::Update(const D3DXVECTOR2 * Pos)
{
	if (button2D.size() <= 0)return false;

	if (Pos != nullptr)pos = *Pos;

	for (unsigned int bc = 0; bc < button2D.size(); bc++)
	{
		float transVec = 1.0f;
		if (bc > 0)transVec = -1.0f;
		D3DXVECTOR2 p = pos;
		p.x += (transX*transVec);

		button2D[bc]->Update(&p);
	}

	return true;
}

bool C_ArrowsButton::TouchJudg(bool * LeftFlg)
{
	if (button2D.size() <= 0)return false;

	for (unsigned int bc = 0; bc < button2D.size(); bc++)
	{
		if (button2D[bc]->TouchJudg())
		{
			if (bc > 0)
			{
				*LeftFlg = false;
			}
			else {
				*LeftFlg = true;
			}
			return true;
		}
	}

	return false;
}
