#pragma once
#include"../Draw3D_Base2.h"
#include<string>

class C_Draw3D_Base2_New {
public:
	C_Draw3D_Base2_New(C_Draw3D_Base2 * New_Draw3D);
	~C_Draw3D_Base2_New();

	//表示
	void Draw(const D3DXVECTOR3 *CameraPos);

	//更新
	bool Update(void);

	//行列の更新
	void Set_Mat(const D3DXMATRIX *Mat);

	//表示の初期化
	void New(C_Draw3D_Base2 * New_Draw3D);

private:
	C_Draw3D_Base2 * M_Draw;

	//削除
	void Delete(void);
};