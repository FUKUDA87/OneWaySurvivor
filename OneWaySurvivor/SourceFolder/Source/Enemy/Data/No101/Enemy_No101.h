#pragma once
#include"../../EnemyA.h"

class C_Enemy_No101 :public C_EnemyA {
public:
	C_Enemy_No101(const D3DXMATRIX * GroundMat, const float * TransX);
protected:
	//Ô‚Ì“–‚½‚è”»’è—p‚Ìî•ñ‚Ì‰Šú‰»
	void New_Car_Judg_Parts(void);
private:

};