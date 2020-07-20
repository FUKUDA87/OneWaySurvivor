#include "TextureBase.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

void C_TextureBase::Texture_Load(std::string FileName, const int Width, const int Height)
{
	M_Tex = { NULL,Width,Height };
	textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, NULL);
}

void C_TextureBase::Texture_Load(std::string FileName, const int Width, const int Height, const int r, const int g, const int b)
{
	M_Tex = { NULL,Width,Height };
	textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, D3DCOLOR_XRGB(r, g, b));
}
