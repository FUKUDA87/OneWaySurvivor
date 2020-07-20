#include "Pause.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

Pause::Pause()
{
	pau.TEX = { NULL,250,50 };
	pau.TEX.Tex = textureManager.GetTexture("CharPause1.png", pau.TEX.Width, pau.TEX.Height, NULL);
	D3DXMatrixTranslation(&pau.Base.Mat, SCRW / 2.0f, SCRH / 2.0f, 0.0f);
	pau.Base.DrawFlg = false;

	// 薄い黒の初期化
	fadeDraw = new C_FadeDraw();
	alpha = 150;

	StageSaveFlg = false;
}

Pause::~Pause()
{
	if (fadeDraw != nullptr)delete fadeDraw;
}

void Pause::Draw()
{
	if (pau.Base.DrawFlg == true) {

		// 薄い黒の表示
		if (fadeDraw != nullptr) {
			int Color = 0;
			fadeDraw->Draw(&alpha, &Color);
		}

		// ポーズ表示
		RECT rcH = { 0,0,pau.TEX.Width,pau.TEX.Height };
		lpSprite->SetTransform(&pau.Base.Mat);
		lpSprite->Draw(pau.TEX.Tex, &rcH, &D3DXVECTOR3((float)pau.TEX.Width / 2.0f, (float)pau.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}
