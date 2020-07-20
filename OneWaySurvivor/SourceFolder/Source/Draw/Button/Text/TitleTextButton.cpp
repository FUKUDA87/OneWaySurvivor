#include "TitleTextButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_TitleTextButton::C_TitleTextButton(const D3DXVECTOR2 * Pos, const float s, const bool * PushFlg)
{
	float rate = 1.0f;

	if (*PushFlg == false)
	{
		width = 350;
		height = 92;
		Tex = textureManager.GetTexture("CharTitle1.png", width, height, NULL);

	}else{
		width = 364;
		height = 106;
		Tex = textureManager.GetTexture("CharTitle1-2.png", width, height, NULL);


		rate = (float)width / 350.0f;
	}

	pos = *Pos;

	rate = s * rate;
	setScalSize(&rate, 5);

	angZ = 0.0f;
}
