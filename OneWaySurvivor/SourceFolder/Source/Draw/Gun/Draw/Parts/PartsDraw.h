#pragma once
#include<d3dx9.h>
#include"../../../../GameSource/Struct.h"
#include"../../../DrawBase2/Draw3D_Base2.h"

class C_PartsDraw_Base {
public:
	C_PartsDraw_Base(C_Draw3D_Base2 *NewDraw);
	~C_PartsDraw_Base();

	//表示
	void Draw(const D3DXVECTOR3 *CameraPos);

	//行列のセット
	virtual void Set_Mat(const D3DXMATRIX *Mat);

	//行列渡し
	virtual D3DXMATRIX Get_Mat(void);
protected:
	/*メンバー変数*/

	C_Draw3D_Base2 *M_Draw_Base;

	/*メンバー関数*/

	//初期化

private:
	/*初期化*/

	//削除
	void Delete_Draw(void);

	//表示の初期化
	void Init_Draw(C_Draw3D_Base2 *NewDraw);
};