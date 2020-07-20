#include "WindowButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_WindowButton::C_WindowButton()
{
	width = 928;
	height = 552;
	Tex = textureManager.GetTexture("frame1to.png", width, height, NULL);

	angZ = 0.0f;
}
