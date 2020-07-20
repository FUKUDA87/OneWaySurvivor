#include"StartTex.h"

StartTex::StartTex()
{
	mod.TEX = { NULL,300,50 };
	mod.TEX.Tex = textureManager.GetTexture("CharStart1.png", mod.TEX.Width, mod.TEX.Height, NULL);
	mod.Base.Pos = D3DXVECTOR2(0.0f, 0.0f);
	mod.Base.ScaPos = D3DXVECTOR2(1.0f, 1.0f);
	wind.Base.ScaPos= D3DXVECTOR2(1.0f*0.3f, 1.0f*0.11f);
	wind.Base.Pos=D3DXVECTOR2((float)SCRW/2.0f+5, (float)SCRH*0.85f);
}

StartTex::~StartTex()
{
}

