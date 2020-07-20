#include "PolMat_Bullet_No1.h"

C_PolMat_Bullet_No1::C_PolMat_Bullet_No1(std::string FileName, const S_TEX_POS * Pos, const S_PolMat_INIT * s_PolMat_Init)
	:C_Draw_PolMat_Base_1(FileName, Pos)
{
	Init_PolMat(s_PolMat_Init->PolNum);
	Init_PolMat_Mat(&s_PolMat_Init->Mat);
	M_ScalPos.x = s_PolMat_Init->PolSize;
}

