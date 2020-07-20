#include "GameOver.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

C_Game_Over::C_Game_Over()
{
	Game_End_Flg = true;

	gaov.TEX = { NULL,502,85 };
	gaov.TEX.Tex = textureManager.GetTexture("CharGameOver3.png", gaov.TEX.Width, gaov.TEX.Height, NULL);
	D3DXMatrixTranslation(&gaov.Base.Mat, (float)SCRW / 2.0f, (float)SCRH / 2.0f, NULL);
}

C_Game_End_Base * C_Game_Over::Change(const int * Mode)
{
	return nullptr;
}

void C_Game_Over::Draw_2D(void)
{
	RECT rcGa = { 0,0,gaov.TEX.Width, gaov.TEX.Height };
	lpSprite->SetTransform(&gaov.Base.Mat);
	lpSprite->Draw(gaov.TEX.Tex, &rcGa, &D3DXVECTOR3((float)gaov.TEX.Width / 2.0f, (float)gaov.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
}
