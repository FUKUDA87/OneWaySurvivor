#include "PolMatBase.h"
#include"../../../../GameSource/Judgment.h"


C_PolMatBase::C_PolMatBase()
{
	Init_PolMat(1);
}

C_PolMatBase::~C_PolMatBase()
{
	Delete_PolMat();
}

void C_PolMatBase::SetMat_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	Judg judg;

	if (PolMat_Judg() != true)return;

	for (int i = 0; i < M_Polygon.Num; i++) {
		judg.VecMatIn(&M_Polygon.Mat[i], MoveVec);
	}
}

void C_PolMatBase::SetMat_Mat(const D3DXMATRIX * Mat)
{
	if (PolMat_Judg(2) != true)return;

	for (int p = M_Polygon.Num - 1; p > 0; p--) {
		M_Polygon.Mat[p] = M_Polygon.Mat[p - 1];
	}
	M_Polygon.Mat[0] = *Mat;
}

void C_PolMatBase::Init_PolMat(const int PolNum)
{
	Delete_PolMat();

	int Num = PolNum;
	if (Num < 1)Num = 1;
	M_Polygon.Num = Num;

	M_Polygon.Mat = new D3DXMATRIX[M_Polygon.Num];
}

void C_PolMatBase::Delete_PolMat(void)
{
	if (M_Polygon.Mat == nullptr)return;

	delete[] M_Polygon.Mat;
}

void C_PolMatBase::Init_PolMat_Mat(const D3DXMATRIX * Mat)
{
	if (PolMat_Judg() != true)return;

	for (int p = 0; p < M_Polygon.Num; p++) {
		M_Polygon.Mat[p] = *Mat;
	}
}

bool C_PolMatBase::PolMat_Judg(void)
{
	if (M_Polygon.Mat == nullptr)return false;
	if (M_Polygon.Num < 1)return false;

	return true;
}

bool C_PolMatBase::PolMat_Judg(const int PolNum)
{
	int Num = PolNum;
	if (Num < 1)Num = 1;

	if (M_Polygon.Mat == nullptr)return false;
	if (M_Polygon.Num < Num)return false;

	return true;
}
