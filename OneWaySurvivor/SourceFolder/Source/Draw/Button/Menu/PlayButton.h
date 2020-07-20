#pragma once
#include"ButtonGameScene.h"

class c_PlayButton :public c_ButtonGameScene
{
public:
	c_PlayButton(const D3DXVECTOR2 *Pos, const float PosY);

	void SetDrawChangeFlg(const bool Flg);
};