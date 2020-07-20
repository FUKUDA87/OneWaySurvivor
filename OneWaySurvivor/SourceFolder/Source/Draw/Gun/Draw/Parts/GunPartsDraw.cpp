#include "GunPartsDraw.h"
#include"../../../../GameSource/Judgment.h"

C_PartsDraw_Gun::C_PartsDraw_Gun(C_Draw3D_Base2 *NewDraw, const S_Gun_Parts_Data *Data)
{
	Draw_New(NewDraw);
	Set_Parts_Data(Data);
}

D3DXVECTOR3 C_PartsDraw_Gun::Get_Gun_Mouth_Pos(void)
{
	D3DXVECTOR3 Pos=M_Data.MouthPos;

	Judg judg;

	Pos = judg.GetVecVec(&Pos, &Get_Draw_ScalPos());

	return Pos;
}

void C_PartsDraw_Gun::Set_Mat(const D3DXMATRIX * Mat)
{
	M_Base3D.Mat = *Mat;

	M_Base3D.Mat = Get_Parts_TransMat() *M_Base3D.Mat;

	Set_All_Draw_Mat(&M_Base3D.Mat);
}

bool C_PartsDraw_Gun::Get_Bullet_Shot_Flg(void)
{
	if (M_Data.BulletFlg != true)return false;

	return true;
}

D3DXMATRIX C_PartsDraw_Gun::Get_Parts_TransMat(void)
{

	Judg judg;

	D3DXMATRIX Mat = judg.getTransMat(&judg.GetVecVec(&M_Data.TarnsPos, &Get_Draw_ScalPos()));

	return Mat;
}

void C_PartsDraw_Gun::Set_Parts_Data(const S_Gun_Parts_Data *Data)
{
	M_Data = *Data;
}
