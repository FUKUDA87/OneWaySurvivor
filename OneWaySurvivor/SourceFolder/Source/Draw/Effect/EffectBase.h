#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class c_EffectBase
{
public:
	// XVˆ—
	virtual bool Update(void) { return false; };
	virtual bool Update(const s_CarEffectUpdateData *updateData) { return false; };

	// •\¦
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos) {};
};