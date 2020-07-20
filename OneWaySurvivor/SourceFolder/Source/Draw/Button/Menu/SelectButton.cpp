#include "SelectButton.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../Scene/SceneNo.h"
#include"../Text/SelectTextButton.h"

extern TextureManager textureManager;

c_SelectButton::c_SelectButton(const D3DXVECTOR2 * Pos, const float PosY)
{
	nextNo = co_StageSelectScene;

	// à íuÇÃèâä˙âª
	transPos = D3DXVECTOR2(5.0f, PosY);
	pos = *Pos + transPos;

	button2D.push_back(new C_SelectTextButton(&pos, 50.0f, &DrawChangeFlg));
}

void c_SelectButton::SetDrawChangeFlg(const bool Flg)
{
	if (DrawChangeFlg != Flg)
	{
		Delete();
		button2D.push_back(new C_SelectTextButton(&pos, 50.0f, &Flg));
	}

	DrawChangeFlg = Flg;
}
