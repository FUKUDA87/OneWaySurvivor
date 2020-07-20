#pragma once
#include"Ball3DEffect.h"

class C_Ball3DVec :public c_Ball3DEffect
{
public:
	C_Ball3DVec(const D3DXVECTOR3 *v,const float *r);
	C_Ball3DVec(const D3DXVECTOR3 *v, const float *r,float a);

	// XVˆ—
	bool Update(const s_CarEffectUpdateData *updateData);
private:
	D3DXVECTOR3 Vec;
};