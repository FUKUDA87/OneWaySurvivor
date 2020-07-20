#pragma once
#include<d3dx9.h>
#include<vector>
#include"Button2D.h"

class C_ButtonBase
{
public:
	~C_ButtonBase();

	// 表示
	virtual void Draw2D(void);

	// 更新処理
	virtual bool Update(const D3DXVECTOR2 *Pos);

	// タッチ判定
	virtual bool TouchJudg(void);

protected:
	std::vector<C_Button2D*>button2D;

	D3DXVECTOR2 pos;  // 位置


	void Delete(void);
};