#include "ArrowButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_ArrowButton::C_ArrowButton(const D3DXVECTOR2 * Pos, const D3DXVECTOR2 * Scal, const bool ReverseFlg)
{
	width = 150;
	height = 148;
	Tex = textureManager.GetTexture("Arr2-2.png", width, height, NULL);

	pos = *Pos;
	scalSize = *Scal;

	if (ReverseFlg == false)
	{
		angZ = 0.0f;
	}
	else {
		angZ = 180.0f;
	}
}
