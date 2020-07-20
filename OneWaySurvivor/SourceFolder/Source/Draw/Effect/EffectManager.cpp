#include "EffectManager.h"

bool C_EffectManager::Update(void)
{
	if (effect.size() < 1)return false;

	for (unsigned int ec = 0; ec < effect.size(); ec++) {
		if (effect[ec]->Update() != true)Delete(&ec);
	}

	return true;
}

void C_EffectManager::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	if (effect.size() < 1)return;

	for (auto && e : effect)e->Draw3D(CameraPos);
}

void C_EffectManager::Delete(void)
{
	if (effect.size() < 1)return;

	//‘S‚Äíœ
	for (unsigned int ec = 0; ec < effect.size(); ec++) {
		delete effect[ec];
		effect.erase(effect.begin() + (ec));
		ec--;
	}
}

void C_EffectManager::Delete(unsigned int * count)
{
	//1‚Âíœ
	delete effect[*count];
	effect.erase(effect.begin() + (*count));
	*count -= 1;
}
