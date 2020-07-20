#pragma once
#include"GunMoveBase_A.h"

//Žè“®
class C_GunManual_1_1 :public C_GunMoveBase_A {
public:
	C_GunManual_1_1();
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:

private:
	D3DXMATRIX RotXMat;
};