#pragma once
#include"Damage_Num_Base.h"

class C_Damage_Move_A :public C_Damage_Num_Base {
public:
	C_Damage_Move_A(const D3DXVECTOR3 *Pos_3D, const D3DXMATRIX * Mat, const int *Damage_Num);
protected:
	void Move(void);
private:
	float UpY;
	D3DXVECTOR2 UpVec,Pos;
};