#include "Ball3DVec.h"
#include"../../../../GameSource/Judgment.h"

C_Ball3DVec::C_Ball3DVec(const D3DXVECTOR3 * v, const float * r) : c_Ball3DEffect(*r)
{
	Vec = *v;
}

C_Ball3DVec::C_Ball3DVec(const D3DXVECTOR3 * v, const float * r, float a) : c_Ball3DEffect(*r,a)
{
	Vec = *v;
}

bool C_Ball3DVec::Update(const s_CarEffectUpdateData * updateData)
{
	if (ball3D == nullptr)return false;

	D3DXVECTOR3 pos;
	D3DXVec3TransformCoord(&pos, &Vec, &updateData->Mat);
	ball3D->SetPos(&pos);

	return true;
}
