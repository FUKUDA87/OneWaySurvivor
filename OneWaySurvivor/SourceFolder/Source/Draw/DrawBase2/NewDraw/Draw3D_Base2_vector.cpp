#include "Draw3D_Base2_vector.h"

C_Draw3D_Base2_vector::~C_Draw3D_Base2_vector()
{
	Delete_All();
}

void C_Draw3D_Base2_vector::Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw.size() < 1)return;

	for (auto && d : M_Draw) {
		d->Draw3D(CameraPos);
	}
}

bool C_Draw3D_Base2_vector::Update(void)
{
	if (M_Draw.size() < 1)return false;

	for (auto && d : M_Draw) {
		if (d->Update() != true) {

		}
	}

	return true;
}

void C_Draw3D_Base2_vector::Set_Mat(const D3DXMATRIX * Mat)
{
	if (M_Draw.size() < 1)return;

	for (auto && d : M_Draw) {
		d->Set_Mat(Mat);
	}
}

void C_Draw3D_Base2_vector::New(C_Draw3D_Base2 * New_Draw3D)
{
	M_Draw.push_back(New_Draw3D);
}

void C_Draw3D_Base2_vector::Delete(void)
{
}

void C_Draw3D_Base2_vector::Delete_All(void)
{
	if (M_Draw.size() < 1)return;

	for (unsigned int d = 0; d < M_Draw.size(); d++) {
		delete M_Draw[d];
		M_Draw.erase(M_Draw.begin() + d);
		d--;
	}
}
