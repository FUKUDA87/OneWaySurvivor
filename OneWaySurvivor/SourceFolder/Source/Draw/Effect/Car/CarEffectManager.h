#pragma once
#include"../EffectManager.h"
#include"../../../GameSource/Struct.h"

class C_CarEffectManager :public C_EffectManager
{
public:
	// XVˆ—
	virtual bool Update(const s_CarEffectUpdateData *updateData);
};