#pragma once
#include"SparkBase.h"

class C_WallSideHitSpark :public C_SparkBase
{
public:
	C_WallSideHitSpark(const D3DXMATRIX *InitMat, const bool *InitFlg,const bool *LeftFlg);
};