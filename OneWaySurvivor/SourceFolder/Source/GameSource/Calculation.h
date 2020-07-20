#pragma once
#include<d3dx9.h>
#include<stdlib.h>
/*#include<windows.h>
#include<stdio.h>
#include<time.h>*/

#ifndef Calcul_H
#define Calcul_H

class Cal {
private:
protected:
public:
	double absd(double d);
	int absi(double d);
	D3DXMATRIX CroDot(D3DXMATRIX *Mat,D3DXMATRIX tarMat,D3DXVECTOR3 FrontVec);
	D3DXMATRIX CroDot(D3DXMATRIX *Mat, D3DXMATRIX tarMat, D3DXVECTOR3 FrontVec,float f);
	bool BoaPolLei(D3DXMATRIX Mat, D3DXMATRIX eMat, D3DXMATRIX pMat, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2,D3DXMATRIX point);
};

#endif // !Calcul_H
