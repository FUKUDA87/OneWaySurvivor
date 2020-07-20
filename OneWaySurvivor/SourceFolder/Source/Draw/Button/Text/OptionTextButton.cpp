#include "OptionTextButton.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_OptionTextButton::C_OptionTextButton()
{
	width = 169;
	height = 50;
	Tex = textureManager.GetTexture("OptionText.png", width, height, NULL);

	angZ = 0.0f;
}
