#pragma once
#include"LaserBase2.h"

class C_LaserDraw1 :public C_LaserBase2 {
public:
	C_LaserDraw1(const int *TexNo);
	virtual void Draw3DAll(const D3DXMATRIX* Mat, const D3DXVECTOR3*TransPos, const float*PolSize, const D3DXVECTOR3*CamPos, const float*Dis, const bool*DrawFlg);
	void Draw3D_1(const D3DXVECTOR3*StartPos, const D3DXVECTOR3*HitPos, const D3DXVECTOR3 * CamPos, const float*PolSize, const bool*DrawFlg);
protected:
	bool Draw1Flg;
private:

};