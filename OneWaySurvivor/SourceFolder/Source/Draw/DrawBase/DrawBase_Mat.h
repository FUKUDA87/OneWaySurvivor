#pragma once
#include"DrawBase.h"

class C_DrawBase_Mat :public C_DrawBase {
public:
	//C_DrawBase_Mat();
protected:

private:
	D3DXMATRIX RotXMat, RotYMat, RotZMat;
};