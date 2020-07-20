#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"

class c_Screen
{
public:
	c_Screen();
	~c_Screen();

	// �X�V����
	bool Update(const bool *KeyFlg);

	// �\��
	void Draw2D(void);

	bool RenderStart(const D3DXMATRIX *Mat);
	void RenderEnd(void);
private:
	
	LPDIRECT3DSURFACE9 lpBackBuffer;     // �o�b�N�o�b�t�@
	LPDIRECT3DSURFACE9 lpZBuffer;        // Z�o�b�t�@
	LPDIRECT3DSURFACE9 lpTmpBackBuffer;  // ���o�b�N�o�b�t�@
	LPDIRECT3DSURFACE9 lpTmpZBuffer;     // ��Z�o�b�N�o�b�t�@
	LPDIRECT3DTEXTURE9 lpTmpTex;         // ���o�b�N�o�b�t�@�̃e�N�X�`���`��

	bool DrawFlg;                        // �\�����邩�ǂ�����Flg
	
};