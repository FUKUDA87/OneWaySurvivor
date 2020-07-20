#pragma once
#include<d3dx9.h>
#include"../Const/PhaseConst.h"
#include"../../../GameSource/Struct.h"

class C_Speed_Update {
public:
	virtual C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData *UpdateData) = 0;
protected:
	//アップタイミング
	int CountDown, CountDownNow;
	bool CountUpdate(void);
	int NowPhase;


};