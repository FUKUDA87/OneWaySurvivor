#include "TitleButton.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../Scene/SceneNo.h"
#include"../Text/TitleTextButton.h"

extern TextureManager textureManager;

c_TitleButton::c_TitleButton(const D3DXVECTOR2 *Pos, const float PosY)
{
	nextNo = co_TitleScene;

	// à íuÇÃèâä˙âª
	transPos = D3DXVECTOR2(0.0f, PosY);
	pos = *Pos + transPos;

	button2D.push_back(new C_TitleTextButton(&pos, 50.0f, &DrawChangeFlg));

}

void c_TitleButton::SetDrawChangeFlg(const bool Flg)
{
	if (DrawChangeFlg != Flg)
	{
		Delete();
		button2D.push_back(new C_TitleTextButton(&pos, 50.0f, &Flg));
	}

	DrawChangeFlg = Flg;
}
