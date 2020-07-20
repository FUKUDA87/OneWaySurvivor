#include "HpbarBase.h"

float C_HpbarBase::GetGage(const int * NowHp, const int * MaxHp)
{
	int s = *NowHp, e = *MaxHp;
	if (s > e)s = e;
	if (s < 0)s = 0;
	float Per = ((float)s) / ((float)e);
	if (Per < 0.0f) {
		Per = 0.0f;
	}
	return Per;
}

D3DXVECTOR2 C_HpbarBase::GetTexPos(const D3DXVECTOR2 * TexPos, const D3DXVECTOR2 * TransPos, const D3DXVECTOR2 * ScalPos)
{
	D3DXVECTOR2 Pos;
	Pos.x = TransPos->x - (TexPos->x*ScalPos->x / 2.0f);
	Pos.y = TransPos->y - (TexPos->y*ScalPos->y / 2.0f);
	return Pos;
}
