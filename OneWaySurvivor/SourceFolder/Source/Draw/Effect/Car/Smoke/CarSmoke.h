#pragma once
#include"../CarEffectManager.h"

class c_CarSmoke:public C_CarEffectManager
{
public:
	// �X�V����
	bool Update(const s_CarEffectUpdateData *updateData);
};