#include "Enemy_Manager.h"
#include"../No101/Enemy_No101.h"

C_EnemyAi * C_Enemy_Manager::Get_Enemy(const int * EnemyNo,const D3DXMATRIX *GroundMat,const float * TransX)
{
	switch (*EnemyNo)
	{
	case 1:
		return new C_Enemy_No1(GroundMat, TransX);
		break;
	case 101:
		return new C_Enemy_No101(GroundMat, TransX);
		break;
	}

	return new C_Enemy_No1(GroundMat,TransX);
}
