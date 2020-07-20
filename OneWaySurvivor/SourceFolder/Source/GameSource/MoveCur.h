#pragma once
#include<d3dx9.h>
#include"Struct.h"

class MoveCur {
public:
	//レール移動
	void RailC(D3DXMATRIX *mat, float f);
	//カーブ
	void Curve(CHARA3D *chara);
};