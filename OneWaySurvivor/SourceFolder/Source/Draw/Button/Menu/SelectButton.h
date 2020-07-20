#pragma once
#include"ButtonGameScene.h"

class c_SelectButton :public c_ButtonGameScene
{
public:
	c_SelectButton(const D3DXVECTOR2 *Pos, const float PosY);

	void SetDrawChangeFlg(const bool Flg);
};