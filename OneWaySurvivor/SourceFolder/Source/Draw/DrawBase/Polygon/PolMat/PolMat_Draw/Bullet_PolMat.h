#pragma once
#include"../PolMatBase.h"
#include"../../../../../GameSource/GetSet/Int_GetSet.h"
#include"../../../../../GameSource/GetSet/float_GetSet.h"


class C_Bullet_PolMat :public C_PolMatBase {
public:
	C_Bullet_PolMat(const int *BulletTexNo,const float *PolSize,const int *PolNum);
	~C_Bullet_PolMat();

	//•\¦
	void DrawBase(const D3DXVECTOR3 *CameraPos);

protected:

private:
	//Å’áƒ|ƒŠƒSƒ“”
	C_Int *M_PolNumLine;
	C_Float *M_PolSize;

	//‰Šú‰»
	void Init_Draw(void);

	//íœ
	void Delete_Draw(void);
};