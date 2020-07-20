#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Judgment.h"

class C_GunMove {
public:
	virtual C_GunMove *Action(GUNAI* GunAi) = 0;
protected:
	Judg judg;
};