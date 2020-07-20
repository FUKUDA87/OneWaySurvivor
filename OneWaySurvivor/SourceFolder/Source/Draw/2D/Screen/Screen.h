#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"

class c_Screen
{
public:
	c_Screen();
	~c_Screen();

	// 更新処理
	bool Update(const bool *KeyFlg);

	// 表示
	void Draw2D(void);

	bool RenderStart(const D3DXMATRIX *Mat);
	void RenderEnd(void);
private:
	
	LPDIRECT3DSURFACE9 lpBackBuffer;     // バックバッファ
	LPDIRECT3DSURFACE9 lpZBuffer;        // Zバッファ
	LPDIRECT3DSURFACE9 lpTmpBackBuffer;  // 裏バックバッファ
	LPDIRECT3DSURFACE9 lpTmpZBuffer;     // 裏Zバックバッファ
	LPDIRECT3DTEXTURE9 lpTmpTex;         // 裏バックバッファのテクスチャ形式

	bool DrawFlg;                        // 表示するかどうかのFlg
	
};