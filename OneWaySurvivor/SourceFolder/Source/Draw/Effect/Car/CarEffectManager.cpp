#include "CarEffectManager.h"

bool C_CarEffectManager::Update(const s_CarEffectUpdateData * updateData)
{
	if (effect.size() < 1)return false;

	for (unsigned int ec = 0; ec < effect.size(); ec++) {
		if (effect[ec]->Update(updateData) != true)Delete(&ec);
	}

	return true;
}
