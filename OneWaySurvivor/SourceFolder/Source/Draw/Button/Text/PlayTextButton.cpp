#include "PlayTextButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_PlayTextButton::C_PlayTextButton(const D3DXVECTOR2 * Pos, const float s, const bool * PushFlg)
{
	float rate = 1.0f;

	if (*PushFlg == false)
	{
		width = 329;
		height = 92;
		Tex = textureManager.GetTexture("CharPlay1.png", width, height, NULL);
	}
	else {
		width = 343;
		height = 106;
		Tex = textureManager.GetTexture("CharPlay1-2.png", width, height, NULL);

		rate = (float)width / 329.0f;
	}

	pos = *Pos;

	rate = s * rate;

	setScalSize(&rate, 4);

	angZ = 0.0f;
}
