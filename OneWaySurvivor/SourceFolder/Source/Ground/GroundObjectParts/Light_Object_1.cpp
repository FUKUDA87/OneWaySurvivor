#include "Light_Object_1.h"
#include"../../GameSource/Judgment.h"

C_Light_Object_1::C_Light_Object_1()
{
	Mesh_Load("LightWay2.x");
}

void C_Light_Object_1::Update_DrawMat(const D3DXMATRIX * Mat)
{
	M_Base.Base.Mat = M_Base.Base.RotY*M_Base.Base.Trans*(*Mat);

	M_Base.Base.DrawMat = M_Base.Base.Scal*M_Base.Base.Mat;
}

void C_Light_Object_1::Init(void)
{
	Judg judg;

	float Size = 5.0f;
	judg.Get_Size3D(&M_Base.Base.ScaPos, &Size);

	judg.setScalingMat(&M_Base.Base.Scal, &M_Base.Base.ScaPos);

	judg.setTransMat(&M_Base.Base.Trans, &D3DXVECTOR3(-1.0f, 5.0f, 0.0f));

	D3DXMatrixRotationY(&M_Base.Base.RotY, D3DXToRadian(90.0f));
}
