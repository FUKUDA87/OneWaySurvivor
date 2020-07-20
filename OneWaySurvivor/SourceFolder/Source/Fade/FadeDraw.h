#pragma once
#include<d3dx9.h>

class C_FadeDraw
{
public:
	C_FadeDraw();

	// •`‰æ
	void Draw(const int *a, const int *r, const int *g, const int *b);
	void Draw(const int *a, const int *Color);

private:
	LPDIRECT3DTEXTURE9 fadeTex;
};