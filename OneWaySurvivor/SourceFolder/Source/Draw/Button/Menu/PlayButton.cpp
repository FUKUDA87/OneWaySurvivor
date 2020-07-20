#include "PlayButton.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../Scene/SceneNo.h"
#include"../Text/PlayTextButton.h"

extern TextureManager textureManager;

c_PlayButton::c_PlayButton(const D3DXVECTOR2 * Pos, const float PosY)
{
	nextNo = co_PlayGame;

	// à íuÇÃèâä˙âª
	transPos = D3DXVECTOR2(0.0f, PosY);
	pos = *Pos + transPos;

	button2D.push_back(new C_PlayTextButton(&pos, 50.0f, &DrawChangeFlg));
}

void c_PlayButton::SetDrawChangeFlg(const bool Flg)
{
	if (DrawChangeFlg != Flg)
	{
		Delete();
		button2D.push_back(new C_PlayTextButton(&pos, 50.0f, &Flg));
	}

	DrawChangeFlg = Flg;
}
