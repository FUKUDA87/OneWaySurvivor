#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../GameSource/Count/Countdown.h"

class Vector {
private:
	CHARA2D vector,vectorC;
	float f;
	D3DXMATRIX NowMat,NowTrans;
	float NowAng;
	Cou *cou;
	int NowCount,CountEnd;
public:
	void Init();
	Vector() { Init(); };
	~Vector();
	bool Update(const D3DXVECTOR3 *Pos_2D, const D3DXMATRIX *Mat, const D3DXVECTOR3 *CameraPos);
	void Draw(bool b);
	//debug—p
	float GetAng(void) { return vector.Base.AngZ; };
};