#include "CarSmogManager.h"
#include"../../../GameSource/Judgment.h"

D3DXMATRIX C_CarSmogManager::GetPos(const int * CarNo)
{
	Judg judg;

	switch (*CarNo)
	{
	case CarNo1:
		return judg.getTransMat(&D3DXVECTOR3(0.0f, 0.38f, 0.75f));
		break;
	case CarNo2:
		return judg.getTransMat(&D3DXVECTOR3(0.0f, 0.33f, 0.66f));
		break;
	case CarNo101:
		return judg.getTransMat(&D3DXVECTOR3(0.0f, 0.14f, 0.82f));
		break;
	case CarNo201:
		return judg.getTransMat(&D3DXVECTOR3(0.0f, 0.37f, 0.56f));
		break;
	}

	return judg.getTransMat(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

S_Smoke C_CarSmogManager::GetSmog(const int * CarNo)
{
	Judg judg;

	switch (*CarNo)
	{
	case CarNo1:
		return GetInitSmog(&D3DXVECTOR3(0.0f, 0.06f, -0.1f), &D3DXVECTOR3(1000.0f, 1000.0f, 100.0f),
			255, 1000, 2, 0.8f, 0.8f, 0.02f, &judg.GetInitRand(25, 10, 5));
		break;
	case CarNo2:
		return GetInitSmog(&D3DXVECTOR3(0.0f, 0.06f, -0.1f), &D3DXVECTOR3(1000.0f, 1000.0f, 100.0f),
			255, 1000, 2, 0.8f, 0.8f, 0.02f, &judg.GetInitRand(25, 10, 5));
		break;
	}

	return GetInitSmog(&D3DXVECTOR3(0.0f, 0.05f, -0.08f), &D3DXVECTOR3(1000.0f, 1000.0f, 100.0f),
		255, 1000, 2, 0.8f, 0.8f, 0.02f, &judg.GetInitRand(25, 10, 5));
}

S_Smoke C_CarSmogManager::GetInitSmog(const D3DXVECTOR3 * MoveVec, const D3DXVECTOR3 * Frame, const int Alpha, const int AStart, const int ADown, const float PolSize, const float PolBit, const float PolBitUp, const S_Random * Random)
{
	S_Smoke L_S_Smog;
	L_S_Smog.MoveVec = *MoveVec;
	L_S_Smog.Frame = *Frame;
	L_S_Smog.Alpha = Alpha;
	L_S_Smog.AStart = AStart;
	L_S_Smog.ADown = ADown;
	L_S_Smog.PolSize = PolSize;
	L_S_Smog.PolBit = PolBit;
	L_S_Smog.PolBitUp = PolBitUp;
	L_S_Smog.Random = *Random;

	return L_S_Smog;
}
