#include "PartsDraw.h"


C_PartsDraw_Base::C_PartsDraw_Base(C_Draw3D_Base2 *NewDraw)
{
	Init_Draw(NewDraw);
}

C_PartsDraw_Base::~C_PartsDraw_Base()
{
	Delete_Draw();
}

void C_PartsDraw_Base::Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw_Base == nullptr)return;

	M_Draw_Base->Draw3D(CameraPos);
}

void C_PartsDraw_Base::Set_Mat(const D3DXMATRIX * Mat)
{
	if (M_Draw_Base == nullptr)return;

	M_Draw_Base->Set_Mat(Mat);
}

D3DXMATRIX C_PartsDraw_Base::Get_Mat(void)
{
	


	return M_Draw_Base->Get_Mat();
}

void C_PartsDraw_Base::Init_Draw(C_Draw3D_Base2 * s_Draw)
{
	Delete_Draw();

	M_Draw_Base = s_Draw;
}

void C_PartsDraw_Base::Delete_Draw(void)
{
	if (M_Draw_Base == nullptr)return;

	delete M_Draw_Base;

}
