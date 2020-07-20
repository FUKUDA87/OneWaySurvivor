#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"
#include"../../../../GameSource/Count/CountBase.h"

class C_SparkBase :public c_EffectBase
{
public:
	C_SparkBase();
	~C_SparkBase();

	// 更新処理
	bool Update(void);

	// 表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:

	VERTEX v[4];
	LPDIRECT3DTEXTURE9 Tex;
	D3DXMATRIX Mat;

	D3DXMATRIX *PolMat;
	int PolNum;
	float PolSize;  // 横幅
	
	float yUp, yDown;  // ジャンプ移動の変数
	float zDown;       // 後ろ方向に移動させる
	C_CountBase *count;// 時間で削除

	bool updateStartFlg;  // 更新の開始フラグ

	// ジャンプ処理の更新
	virtual void UpdateMoveY(void);
};