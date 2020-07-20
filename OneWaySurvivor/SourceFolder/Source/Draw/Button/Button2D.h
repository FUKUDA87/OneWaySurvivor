#pragma once
#include<d3dx9.h>

class C_Button2D
{
public:

	// 表示
	void Draw2D(void);

	// 更新処理
	bool Update(const D3DXVECTOR2 *Pos);

	// タッチ判定
	bool TouchJudg(void);

	// 拡縮
	void setScalSize(const D3DXVECTOR2 *s) { scalSize = *s; }
	void setScalSize(const float *s) { scalSize = D3DXVECTOR2(*s, *s); }

protected:

	LPDIRECT3DTEXTURE9 Tex;
	int width, height;  // 画像サイズ

	D3DXVECTOR2 pos,scalSize;  // 位置と拡縮x,y
	float angZ;

	// テキストのサイズ変更
	void setScalSize(const float *s, const int letterNum);
};