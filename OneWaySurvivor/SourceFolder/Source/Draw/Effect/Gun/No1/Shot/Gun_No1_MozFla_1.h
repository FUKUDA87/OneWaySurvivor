#pragma once
#include"../../../../../Draw/DrawBase2/Draw_Pol_A.h"

class C_Gun_No1_MuzFla_1 :public C_Draw_Pol_BASE_A {
public:
	C_Gun_No1_MuzFla_1(const D3DXMATRIX *Gun_Mouth_Mat);

	//表示関数
	void Draw3D(const D3DXVECTOR3 *CameraPos);

	bool Update(void);
protected:

	//テクスチャのロード
	void Init_Load(void);

	//行列の初期化
	void Init_Mat(const D3DXMATRIX *Gun_Mouth_Mat);

	//ポリゴンの初期化
	void Init_Pol_Set(void);

	bool AliveFlg;
private:

};