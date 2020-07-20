#pragma once
#include"../No1/Enemy_No1.h"

class C_Enemy_Manager {
public:
	C_EnemyAi* Get_Enemy(const int *EnemyNo, const D3DXMATRIX * GroundMat, const float * TransX);
};