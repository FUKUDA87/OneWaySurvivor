#include "DrawTextureManager_Base.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

TEXTURE C_DrawTextureManager_Base::Texture_Load(std::string FileName, const int Width, const int Height)
{
	TEXTURE M_Tex;
	M_Tex = { NULL,Width,Height };
	M_Tex.Tex = textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, NULL);

	return M_Tex;
}

TEXTURE C_DrawTextureManager_Base::Texture_Load(std::string FileName, const int Width, const int Height, const int r, const int g, const int b)
{
	TEXTURE M_Tex;
	M_Tex = { NULL,Width,Height };
	M_Tex.Tex = textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, D3DCOLOR_XRGB(r, g, b));

	return M_Tex;
}
