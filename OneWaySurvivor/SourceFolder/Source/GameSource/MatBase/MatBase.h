#pragma once
#include<d3dx9.h>

class C_MatBase {
public:
	//回転X行列作成
	D3DXMATRIX Set_RotXMat(const float *Ang);

	//回転X行列作成
	D3DXMATRIX Set_RotYMat(const float *Ang);

	//回転X行列作成
	D3DXMATRIX Set_RotZMat(const float *Ang);

	//位置の行列作成
	D3DXMATRIX Set_TransMat(const D3DXVECTOR3 *Pos);

	//拡大縮小の行列作成
	D3DXMATRIX Set_ScalMat(const D3DXVECTOR3 *Pos);

	//行列の初期化
	D3DXMATRIX Init_Mat(void);

protected:

private:
	
};