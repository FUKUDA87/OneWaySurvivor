#pragma once
#include"../../Player/PlayerA.h"
#include<d3dx9.h>

class StageCar:public C_PlayerA {
public:
	StageCar(const BODYDATA * Data);
	~StageCar() {};
	//åpè≥
	bool Update(void);
};