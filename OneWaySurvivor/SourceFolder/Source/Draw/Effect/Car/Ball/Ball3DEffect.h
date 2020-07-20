#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"
#include"../../../3D/Ball/Ball3D.h"

class c_Ball3DEffect :public c_EffectBase
{
public:
	c_Ball3DEffect(float Radius) { ball3D = new c_Ball3D(Radius); }
	c_Ball3DEffect(float Radius, float alpha) { ball3D = new c_Ball3D(Radius, alpha); }

	~c_Ball3DEffect() { if (ball3D != nullptr)delete ball3D; }

	// çXêVèàóù
	virtual bool Update(const s_CarEffectUpdateData *updateData);

	// ï\é¶
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:
	c_Ball3D *ball3D;
};