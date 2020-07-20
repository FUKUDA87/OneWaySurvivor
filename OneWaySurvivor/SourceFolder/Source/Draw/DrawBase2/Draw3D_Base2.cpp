#include "Draw3D_Base2.h"
#include"../../GameSource/Judgment.h"

D3DXMATRIX C_Draw3D_Base2::Get_DrawMat(void)
{
	D3DXMATRIX TmpMat;

	Judg judg;

	TmpMat = judg.GetDrawMat(&Get_Mat(), &Get_ScalPos());

	return TmpMat;
}

bool C_Draw3D_Base2::Get_MoveVecFlg(void)
{
	if (MoveVecFlg != false)return true;

	MoveVecFlg = true;

	return false;
}

D3DXMATRIX C_Draw3D_Base2::Get_IdenMat(void)
{
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);

	IdenFlg = true;

	return IdenMat;
}

void C_Draw3D_Base2::Base_Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	Judg judg;

	judg.VecMatIn(&M_Mat, MoveVec);
}

void C_Draw3D_Base2::Set_ScalPos_Init(const D3DXVECTOR3 * set_ScalPos)
{
	M_ScalPos_Init = *set_ScalPos;
	M_ScalPos = M_ScalPos_Init;
}

bool C_Draw3D_Base2::Update(void)
{
	return false;
}

void C_Draw3D_Base2::Set_ScalPos_Update(const D3DXVECTOR3 * set_ScalPos)
{
	Judg judg;
	M_ScalPos_Body = *set_ScalPos;
	M_ScalPos = judg.GetVecVec(&M_ScalPos_Init, &M_ScalPos_Body);
}

D3DXVECTOR3 C_Draw3D_Base2::Get_SizeVec(const float * Size)
{
	D3DXVECTOR3 Vec;
	Vec = D3DXVECTOR3(1.0f,1.0f, 1.0f);
	Vec *= (*Size);
	return Vec;
}

void C_Draw3D_Base2::Init(void)
{
	MoveVecFlg = false;

	Set_ScalPos_Init(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	M_ScalPos_Body = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMatrixTranslation(&M_Mat, 0.0f, 0.0f, 0.0f);
	
	Draw_JudgFlg = 0;

	IdenFlg = false;
}

C_Draw3D_Base2::C_Draw3D_Base2()
{
	Init();
}

void C_Draw3D_Base2::Draw3D(const D3DXVECTOR3 * CameraPos, bool * Body_DamageFlg)
{
}
