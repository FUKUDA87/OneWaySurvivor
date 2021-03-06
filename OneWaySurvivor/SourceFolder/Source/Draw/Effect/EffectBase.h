#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class c_EffectBase
{
public:
	// 更新処理
	virtual bool Update(void) { return false; };
	virtual bool Update(const s_CarEffectUpdateData *updateData) { return false; };

	// 表示
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos) {};
};