#pragma once
#include"../../EnemyA.h"

class C_Enemy_No101 :public C_EnemyA {
public:
	C_Enemy_No101(const D3DXMATRIX * GroundMat, const float * TransX);
protected:
	//車の当たり判定用の情報の初期化
	void New_Car_Judg_Parts(void);
private:

};