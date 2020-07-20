#include "SelectTextButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_SelectTextButton::C_SelectTextButton(const D3DXVECTOR2 * Pos, const float s, const bool * PushFlg)
{
	float rate = 1.0f;

	if (*PushFlg == false)
	{
		width = 453;
		height = 92;
		Tex = textureManager.GetTexture("CharSelect1.png", width, height, NULL);
	}
	else {
		width = 467;
		height = 106;
		Tex = textureManager.GetTexture("CharSelect1-2.png", width, height, NULL);

		rate = (float)width / 453.0f;
	}

	pos = *Pos;

	rate = s * rate;
	setScalSize(&rate, 6);

	angZ = 0.0f;
}
