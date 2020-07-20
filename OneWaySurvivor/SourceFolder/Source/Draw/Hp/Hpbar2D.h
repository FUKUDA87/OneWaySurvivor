#pragma once
#include"HpbarBase.h"

class C_Hpbar2D:public C_HpbarBase {
public:
	C_Hpbar2D();

	// 2D•\Ž¦
	virtual void Draw2D(const int *NowHp, const int *MaxHp);
protected:
	TEXTURE hpTex[2];
	D3DXVECTOR2 Pos,ScalPos;

	void DrawA(const int *NowHp, const int *MaxHp);
};