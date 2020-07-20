#include "StructManager.h"
#include"../GameSource/Judgment.h"

s_CarType c_StructManager::GetCarType(const int * Type, const unsigned int * Number1, const unsigned int * Number2, const unsigned int * Number3)
{
	s_CarType carType;

	carType.Type = *Type;

	if (Number1 != nullptr)
	{
		carType.Numbar[0] = *Number1;
	}
	else {
		carType.Numbar[0] = 0;
	}

	if (Number2 != nullptr)
	{
		carType.Numbar[1] = *Number2;
	}
	else {
		carType.Numbar[1] = 0;
	}

	if (Number3 != nullptr)
	{
		carType.Numbar[2] = *Number3;
	}
	else {
		carType.Numbar[2] = 0;
	}

	return carType;
}

s_CarType c_StructManager::GetCarType(const int * Type, const unsigned int * Number1, const unsigned int * Number2)
{
	return GetCarType(Type, Number1, Number2, nullptr);
}

s_CarType c_StructManager::GetCarType(const int * Type, const unsigned int * Number1)
{
	return GetCarType(Type,Number1,nullptr);
}

s_CarType c_StructManager::GetCarType(const int * Type)
{
	return GetCarType(Type, nullptr, nullptr);
}

BULLETJUDGDATA c_StructManager::GetBULLETJUDGDATA(const s_CarType * carType, const float * Dis)
{
	BULLETJUDGDATA BJD;
	BJD.JudgType = *carType;
	BJD.HitType.Type = -1;
	BJD.SamllDis = *Dis;
	return BJD;
}

S_Capsule c_StructManager::getCapsule(const D3DXMATRIX * m, const D3DXVECTOR3 * scal, const D3DXVECTOR3 * meshBigVec, const D3DXVECTOR3 * meshSmallVec)
{
	S_Capsule c;

	// 半径
	float x1 = meshBigVec->x*scal->x, x2 = meshSmallVec->x*scal->x;
	if (x1 < 0.0f)x1 *= -1.0f;
	if (x2 < 0.0f)x2 *= -1.0f;

	if (x1 < x2)
	{
		c.r = x1;
	}
	else {
		c.r = x2;
	}

	// 始点
	capsuleVecInit(&c.vs, &c.l.s, &c.r, m, scal, meshBigVec);

	// 終点
	if (capsuleVecInit(&c.ve, &c.l.e, &c.r, m, scal, meshSmallVec))
	{
		// 始点
		capsuleVecInit(&c.vs, &c.l.s, &c.r, m, scal, meshBigVec);
	}

	// ベクトル
	c.l.v = c.l.e - c.l.s;

	return c;
}

bool c_StructManager::capsuleVecInit(D3DXVECTOR3 * vi, D3DXVECTOR3 * vj, float * r, const D3DXMATRIX * m, const D3DXVECTOR3 * scal, const D3DXVECTOR3 * meshVec)
{
	*vi = D3DXVECTOR3(0.0f, 0.0f, meshVec->z*scal->z);
	float l = D3DXVec3Length(vi);
	bool rcFlg = false;
	if (l < *r)
	{
		*r = l;
		vi->z = 0.0f;
		rcFlg = true;
	}
	else {
		Judg judg;
		float l2 = l - *r;
		*vi = (*vi)*judg.rate(&l, &l2);
	}
	D3DXVec3TransformCoord(vj, vi, m);
	
	return rcFlg;
}
