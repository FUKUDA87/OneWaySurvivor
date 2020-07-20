#include "Draw3D_Base2_New.h"

C_Draw3D_Base2_New::C_Draw3D_Base2_New(C_Draw3D_Base2 * New_Draw3D)
{
	New(New_Draw3D);
}

C_Draw3D_Base2_New::~C_Draw3D_Base2_New()
{
	Delete();
}

void C_Draw3D_Base2_New::Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw == nullptr)return;

	M_Draw->Draw3D(CameraPos);
}

bool C_Draw3D_Base2_New::Update(void)
{
	if (M_Draw == nullptr)return false;

	return M_Draw->Update();
}

void C_Draw3D_Base2_New::Set_Mat(const D3DXMATRIX *Mat)
{
	if (M_Draw == nullptr)return;

	M_Draw->Set_Mat(Mat);
}

void C_Draw3D_Base2_New::New(C_Draw3D_Base2 * New_Draw3D)
{
	Delete();

	M_Draw = New_Draw3D;
}

void C_Draw3D_Base2_New::Delete(void)
{
	if (M_Draw == nullptr)return;

	delete M_Draw;
}
