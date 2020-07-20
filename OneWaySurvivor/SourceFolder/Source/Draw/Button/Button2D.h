#pragma once
#include<d3dx9.h>

class C_Button2D
{
public:

	// �\��
	void Draw2D(void);

	// �X�V����
	bool Update(const D3DXVECTOR2 *Pos);

	// �^�b�`����
	bool TouchJudg(void);

	// �g�k
	void setScalSize(const D3DXVECTOR2 *s) { scalSize = *s; }
	void setScalSize(const float *s) { scalSize = D3DXVECTOR2(*s, *s); }

protected:

	LPDIRECT3DTEXTURE9 Tex;
	int width, height;  // �摜�T�C�Y

	D3DXVECTOR2 pos,scalSize;  // �ʒu�Ɗg�kx,y
	float angZ;

	// �e�L�X�g�̃T�C�Y�ύX
	void setScalSize(const float *s, const int letterNum);
};