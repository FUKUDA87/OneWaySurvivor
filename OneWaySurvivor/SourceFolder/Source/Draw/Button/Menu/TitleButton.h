#pragma once
#include"ButtonGameScene.h"

class c_TitleButton :public c_ButtonGameScene
{
public:
	c_TitleButton(const D3DXVECTOR2 *pos, const float PosY);

	void SetDrawChangeFlg(const bool Flg);
};