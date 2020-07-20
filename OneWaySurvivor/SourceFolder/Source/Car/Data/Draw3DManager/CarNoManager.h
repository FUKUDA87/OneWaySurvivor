#pragma once
#include"CarMeshManager.h"

class C_CarNoManager :public C_CarMeshManager {
public:
	int GetNextNo(const int *NowNo);

};