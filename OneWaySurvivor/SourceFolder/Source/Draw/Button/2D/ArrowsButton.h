#pragma once
#include<d3dx9.h>
#include"../ButtonBase.h"

class C_ArrowsButton :public C_ButtonBase
{
public:
	C_ArrowsButton(const D3DXVECTOR2 *Pos, const D3DXVECTOR2 *scalSize, const float *TransX);

	// 更新処理
	bool Update(const D3DXVECTOR2 *Pos);

	// タッチ判定
	bool TouchJudg(bool *LeftFlg);
private:
	float transX;
};