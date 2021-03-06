#pragma once
#include"../PolMatBase.h"
#include"../../../../../GameSource/GetSet/Int_GetSet.h"
#include"../../../../../GameSource/GetSet/float_GetSet.h"


class C_Bullet_PolMat :public C_PolMatBase {
public:
	C_Bullet_PolMat(const int *BulletTexNo,const float *PolSize,const int *PolNum);
	~C_Bullet_PolMat();

	//表示
	void DrawBase(const D3DXVECTOR3 *CameraPos);

protected:

private:
	//最低ポリゴン数
	C_Int *M_PolNumLine;
	C_Float *M_PolSize;

	//初期化
	void Init_Draw(void);

	//削除
	void Delete_Draw(void);
};