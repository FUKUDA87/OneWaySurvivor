#pragma once
#include<d3dx9.h>
#include"EffectBase.h"
#include<vector>

class C_EffectManager
{
public:
	~C_EffectManager() { Delete(); }

	// XVˆ—
	virtual bool Update(void);

	// •\¦
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

	void NewEffect(c_EffectBase *newEffect) { effect.push_back(newEffect); }
protected:
	std::vector<c_EffectBase*>effect;

	// íœ
	void Delete(void);
	void Delete(unsigned int *count);
};