#include "ButtonGameScene.h"
#include"../../../GameSource/Judgment.h"
extern LPD3DXSPRITE lpSprite;	// スプライト

c_ButtonGameScene::c_ButtonGameScene()
{
	DrawChangeFlg = false;
}

bool c_ButtonGameScene::Update(const D3DXVECTOR2 * Pos)
{
	pos = *Pos + transPos;

	if (button2D.size() <= 0)return false;

	for (auto && b : button2D)b->Update(&pos);

	return true;
}
