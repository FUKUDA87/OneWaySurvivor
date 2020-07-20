#pragma once
#include"../Hpbar2D.h"
#include"../../Num/2D/Num2DBase.h"


class c_Hpbar2DPlayer :public C_Hpbar2D
{
public:
	c_Hpbar2DPlayer();
	~c_Hpbar2DPlayer();

	// 2D•\Ž¦
	void Draw2D(const int *NowHp, const int *MaxHp);
private:
	c_Num2DBase *numDraw;
	D3DXVECTOR2 InitVec;

	TEXTURE slash;
};