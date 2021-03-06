#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_HpbarBase {
public:
	// 2D表示
	virtual void Draw2D(const int *NowHp, const int *MaxHp) {};

	// 3D表示
	virtual void Draw3D(const int *NowHp, const int *MaxHp
		, const D3DXMATRIX *Mat, const D3DXVECTOR3 *CamPos
		, const D3DXVECTOR3 *CharaScalPos) {};
protected:
	// 割合計算
	float GetGage(const int *NowHp, const int *MaxHp);

	// 
	D3DXVECTOR2 GetTexPos(const D3DXVECTOR2*TexPos, const D3DXVECTOR2*TransPos, const D3DXVECTOR2*ScalPos);

};