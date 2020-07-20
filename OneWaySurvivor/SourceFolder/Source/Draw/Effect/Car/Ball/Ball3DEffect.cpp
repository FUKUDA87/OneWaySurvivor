#include "Ball3DEffect.h"
#include"../../../../GameSource/Judgment.h"

bool c_Ball3DEffect::Update(const s_CarEffectUpdateData * updateData)
{
	if (ball3D == nullptr)return false;

	Judg judg;
	ball3D->SetPos(&judg.SetPosM(&updateData->Mat));

	return true;
}

void c_Ball3DEffect::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	if (ball3D == nullptr)return;

	ball3D->DrawB();
}
