#include "Bullet_DrawManager.h"
#include"Bullet_No2.h"
#include"../../Draw/Gun/Bullet/Const_Bullet_No.h"
#include"Bullet_No99.h"

C_Bullet_Base * C_Bullet_DrawManager::Get_Bullet(const int * BulletNo, const D3DXMATRIX * Mat)
{
	switch (*BulletNo)
	{
	case 1:
		return new C_Bullet_No1(Mat);
		break;
	case 2:
		return new C_Bullet_No2(Mat);
		break;
	case Co_Bullet_No99:
		return new C_Bullet_No99(Mat);
		break;
	default:
		return new C_Bullet_No1(Mat);
		break;
	}
	return new C_Bullet_No1(Mat);
}

C_Bullet_Base * C_Bullet_DrawManager::Get_Bullet(const int * BulletNo, const D3DXMATRIX * Mat, const S_RayHitJudgData * RayData)
{
	switch (*BulletNo)
	{
	case 1:
		return new C_Bullet_No1(Mat, RayData);
		break;
	case 2:
		return new C_Bullet_No2(Mat, RayData);
		break;
	case Co_Bullet_No99:
		return new C_Bullet_No99(Mat,RayData);
		break;
	default:
		return new C_Bullet_No1(Mat, RayData);
		break;
	}
	return new C_Bullet_No1(Mat,RayData);
}
