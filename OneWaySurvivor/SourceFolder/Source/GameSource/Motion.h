#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Ground/Ground_Object.h"
#include<vector>
#include"Judgment.h"
#include"../Key/Key.h"
#include<math.h>

extern Key key;

class Motion {
public:
	Motion();
	//自分ベジェ曲線
	bool Formove(QuaForMove* CarFM,const CONSTITUTION *Con,std::vector<C_Ground_Object*>ground);
private:
	float CurSize;//ベジェ曲線の長さ１に対しての長さ

	void CurveFloat(float *P, const float *A, const float *B, const float *C, const float *AnimeFlame);
	void CurvePos(D3DXVECTOR3 *Pos, const D3DXMATRIX *Start_Mat, const D3DXVECTOR3 *PosV,
		const D3DXMATRIX *End_Mat, const float *AnimeFlame);
};