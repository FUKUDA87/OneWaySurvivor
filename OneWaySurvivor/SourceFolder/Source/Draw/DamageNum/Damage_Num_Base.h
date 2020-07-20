#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Damage_Num_Base {
public:
	C_Damage_Num_Base(const D3DXVECTOR3 *Pos_3D,const D3DXMATRIX * Mat,const int *Damage_Num);

	//更新
	virtual bool Update(void);

	//表示
	void Draw_2D(void);

	//表示の3D座標渡し
	D3DXVECTOR3 Get_Pos_3D(const D3DXMATRIX * Mat);

	//表示の2D座標にセット
	void Set_Pos_2D(const D3DXVECTOR3 *Pos_2D);

protected:
	virtual void Move(void);

	//表示時間
	int M_Count;

	//表示サイズ
	float M_ScalSize;

	//表示座標
	D3DXVECTOR3 M_Pos_2D;

private:

	//表示座標
	D3DXVECTOR3 M_Vec;

	//表示の構造体
	TEXTURE M_TEX;

	//表示Flg
	bool M_Draw_Flg;

	//ダメージ数
	int M_Damage_Num;
};