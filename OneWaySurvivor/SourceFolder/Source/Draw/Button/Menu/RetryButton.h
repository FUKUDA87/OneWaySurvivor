#pragma once
#include"ButtonGameScene.h"

class c_RetryButton :public c_ButtonGameScene
{
public:
	c_RetryButton(const D3DXVECTOR2 *Pos, const float PosY);

	void SetDrawChangeFlg(const bool Flg);
};