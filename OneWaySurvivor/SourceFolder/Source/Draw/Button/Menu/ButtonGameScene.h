#pragma once
#include"../ButtonBase.h"

class c_ButtonGameScene:public C_ButtonBase
{
public:
	c_ButtonGameScene();

	// 更新処理
	bool Update(const D3DXVECTOR2 *Pos);

	bool GetDrawChangeFlg(void) { return DrawChangeFlg; }
	virtual void SetDrawChangeFlg(const bool Flg) { DrawChangeFlg = Flg; }

	// タッチした時に次の動きの番号渡し
	int GetNextNo(void) { return nextNo; }
protected:

	int nextNo;

	D3DXVECTOR2 transPos;  // 基本の位置と移動の位置と拡縮x,y

	bool DrawChangeFlg;  // 表示変更Flg
};