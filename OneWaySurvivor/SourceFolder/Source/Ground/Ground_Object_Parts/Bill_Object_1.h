#pragma once
#include"Object_Base.h"

class C_Bill_Object_1:public C_Object_Base {
public:
	C_Bill_Object_1();

	//表示行列の更新
	void Update_DrawMat(const D3DXMATRIX *Mat);


protected:
	//初期化
	void Init(void);
private:

};