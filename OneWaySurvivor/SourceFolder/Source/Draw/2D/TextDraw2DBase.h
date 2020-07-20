#pragma once
#include<d3dx9.h>
#include<string>

class C_TextDraw2DBase
{
public:
	C_TextDraw2DBase(std::string FileName, const int Width, const int Height, const D3DXVECTOR2 *p, const D3DXVECTOR2 *s);

	// �\��
	void Draw2D(void);

	// �X�V����
	bool Update(const D3DXVECTOR2 *Pos);

private:
	LPDIRECT3DTEXTURE9 Tex;
	int width, height;  // �摜�T�C�Y

	D3DXVECTOR2 pos, scalSize;  // �ʒu�Ɗg�kx,y
};