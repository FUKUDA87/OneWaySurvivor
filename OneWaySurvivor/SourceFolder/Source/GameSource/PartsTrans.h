#pragma once
#include"State.h"

class C_TireMove :public StateMove {
public:
	StateMove* Action(ObjectParts *ObjPar);
};