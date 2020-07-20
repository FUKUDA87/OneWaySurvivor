#include "RetryButton.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../Scene/SceneNo.h"
#include"../Text/RetryTextButton.h"

extern TextureManager textureManager;

c_RetryButton::c_RetryButton(const D3DXVECTOR2 * Pos, const float PosY)
{
	nextNo = co_GameScene;

	// à íuÇÃèâä˙âª
	transPos = D3DXVECTOR2(0.0f, PosY);
	pos = *Pos + transPos;

	button2D.push_back(new C_RetryTextButton(&pos, 50.0f, &DrawChangeFlg));
}

void c_RetryButton::SetDrawChangeFlg(const bool Flg)
{
	if (DrawChangeFlg != Flg)
	{
		Delete();
		button2D.push_back(new C_RetryTextButton(&pos, 50.0f, &Flg));
	}

	DrawChangeFlg = Flg;
}
