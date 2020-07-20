#include "TextDraw2DBase.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_TextDraw2DBase::C_TextDraw2DBase(std::string FileName, const int Width, const int Height, const D3DXVECTOR2 * p, const D3DXVECTOR2 * s)
{
	width = Width;
	height = Height;
	Tex = textureManager.GetTexture(FileName, width, height, NULL);

	pos = *p;
	scalSize = *s;
}

void C_TextDraw2DBase::Draw2D(void)
{
	D3DXMATRIX tmp, ScalMat;
	D3DXMatrixTranslation(&tmp, pos.x, pos.y, NULL);
	D3DXMatrixScaling(&ScalMat, scalSize.x, scalSize.y, NULL);
	tmp = ScalMat * tmp;

	RECT rcH = { 0,0, width, height };
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(Tex, &rcH, &D3DXVECTOR3((float)width / 2.0f, (float)height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

bool C_TextDraw2DBase::Update(const D3DXVECTOR2 * Pos)
{
	if (Pos != nullptr)pos = *Pos;

	return true;
}
