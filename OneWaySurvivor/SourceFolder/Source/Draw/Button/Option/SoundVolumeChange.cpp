#include "SoundVolumeChange.h"

C_SoundVolumeChange::C_SoundVolumeChange(const bool BGMVolumeFlg, const D3DXVECTOR2 * Pos, const int * Volume)
{
	volume = *Volume / 1000 + 10;

	pos = *Pos;

	float x = 130.0f;
	transNum = D3DXVECTOR2(x - 20.0f, 0.0f);
	transText = D3DXVECTOR2(-x, 0.0f);

	D3DXVECTOR2 p = pos + transText;

	if (BGMVolumeFlg == false)
	{
		// SE
		text = new C_TextDraw2DBase("SEText.png", 72, 50, &p, &D3DXVECTOR2(1.0f, 1.0f));
	}
	else {
		// BGM
		text = new C_TextDraw2DBase("BGMText.png", 134, 50, &p, &D3DXVECTOR2(1.0f, 1.0f));
	}

	num = new c_Num2DBase(0);

	p = pos + transNum;
	x = 90.0f;
	arrows = new C_ArrowsButton(&p, &D3DXVECTOR2(0.4f, 0.3f), &x);
}

C_SoundVolumeChange::~C_SoundVolumeChange()
{
	if (arrows != nullptr)delete arrows;
	if (text != nullptr)delete text;
	if (num != nullptr)delete num;
}

bool C_SoundVolumeChange::Update(const bool * KeyFlg, int * Volume)
{
	if (arrows != nullptr)
	{
		D3DXVECTOR2 p = pos + transNum;
		arrows->Update(&p);

		bool hitFlg;
		if (*KeyFlg == true)
		{
			if (arrows->TouchJudg(&hitFlg))
			{
				if (hitFlg == true)
				{
					volume--;
					if (volume < 0)volume = 0;
				}
				else {
					volume++;
					if (volume > 10)volume = 10;
				}

				*Volume = (10 - volume) * -1000;
			}
		}
	}

	D3DXVECTOR2 p = pos + transText;
	if (text != nullptr)text->Update(&p);

	return true;
}

void C_SoundVolumeChange::Draw2D(void)
{
	if (arrows != nullptr)arrows->Draw2D();
	if (text != nullptr)text->Draw2D();

	D3DXVECTOR2 p = pos + transNum;
	if (num != nullptr)num->Draw(&volume, &p, &D3DXVECTOR2(1.0f, 1.0f));
}
