#pragma once
#include<d3dx9.h>
#include<string>

class C_TextDraw2DBase
{
public:
	C_TextDraw2DBase(std::string FileName, const int Width, const int Height, const D3DXVECTOR2 *p, const D3DXVECTOR2 *s);

	// 表示
	void Draw2D(void);

	// 更新処理
	bool Update(const D3DXVECTOR2 *Pos);

private:
	LPDIRECT3DTEXTURE9 Tex;
	int width, height;  // 画像サイズ

	D3DXVECTOR2 pos, scalSize;  // 位置と拡縮x,y
};