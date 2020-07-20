#include "RetryTextButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_RetryTextButton::C_RetryTextButton(const D3DXVECTOR2 * Pos, const float s, const bool * PushFlg)
{
	float rate = 1.0f;

	if (*PushFlg == false)
	{
		width = 418;
		height = 92;
		Tex = textureManager.GetTexture("CharRetry1.png", width, height, NULL);
	}
	else {
		width = 432;
		height = 106;
		Tex = textureManager.GetTexture("CharRetry1-2.png", width, height, NULL);

		rate = (float)width / 418.0f;
	}

	pos = *Pos;

	rate = s * rate;

	setScalSize(&rate, 5);

	angZ = 0.0f;
}
