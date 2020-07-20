#include "Game_Clear.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

C_Game_Clear::C_Game_Clear()
{
	Game_End_Flg = true;

	stcl.TEX = { NULL,777,72 };
	stcl.TEX.Tex = textureManager.GetTexture("Char_StageClear_3.png", stcl.TEX.Width, stcl.TEX.Height, NULL);
	D3DXMatrixTranslation(&stcl.Base.Mat, (float)SCRW / 2.0f, (float)SCRH / 2.0f, NULL);
}

C_Game_End_Base * C_Game_Clear::Change(const int * Mode)
{
	return nullptr;
}

void C_Game_Clear::Draw_2D(void)
{
	RECT rcGa = { 0,0,stcl.TEX.Width, stcl.TEX.Height };
	lpSprite->SetTransform(&stcl.Base.Mat);
	lpSprite->Draw(stcl.TEX.Tex, &rcGa, &D3DXVECTOR3((float)stcl.TEX.Width / 2.0f, (float)stcl.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
}
