#include "Bill_Object_1.h"
#include"../../GameSource/Judgment.h"

C_Bill_Object_1::C_Bill_Object_1()
{
	Mesh_Load("BillBase1A1.x");
}

void C_Bill_Object_1::Update_DrawMat(const D3DXMATRIX * Mat)
{
	M_Base.Base.Mat = M_Base.Base.Trans*(*Mat);

	M_Base.Base.DrawMat = M_Base.Base.Scal*M_Base.Base.Mat;
}

void C_Bill_Object_1::Init(void)
{
	Judg judg;

	float Size = 200.0f;
	judg.Get_Size3D(&M_Base.Base.ScaPos, &Size);

	judg.setScalingMat(&M_Base.Base.Scal, &M_Base.Base.ScaPos);

	judg.setTransMat(&M_Base.Base.Trans, &D3DXVECTOR3(-30.0f, 8.0f, 0.0f));
}
