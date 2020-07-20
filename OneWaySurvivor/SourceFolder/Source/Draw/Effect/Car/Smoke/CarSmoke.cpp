#include "CarSmoke.h"
#include"../../../../GameSource/Judgment.h"
#include"../../3D/Smoke/Smoke.h"

bool c_CarSmoke::Update(const s_CarEffectUpdateData * updateData)
{
	if (effect.size() > 0) {
		for (unsigned int ec = 0; ec < effect.size(); ec++) {
			if (effect[ec]->Update(updateData) != true)Delete(&ec);
		}
	}

	// ‰Œ‚ÌoŒ»
	float L_Per = (float)updateData->CharaBase.NowHp / (float)updateData->CharaBase.MaxHp;
	if (L_Per < 0.3f) {
		float L_Num = 30.0f;
		if (rand() % 100 < (100-(int)(100.0f*L_Per))) {
			NewEffect(new c_Smoke(&updateData->CarNo, &updateData->Mat, &L_Per, &updateData->CharaBase.NowHp));
		}
	}

	return true;
}
