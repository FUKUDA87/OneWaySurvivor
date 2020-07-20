#include "DrawTextureManager_Manager.h"
#include"Bullet/DrawTextureManager_Bullet.h"

C_DrawTextureManager_Base * C_DrawTextureManager_Manager::Get_Manager(const int * ManagerNo)
{
	if (*ManagerNo == 1)return new C_DrawTextureManager_Bullet();

	return new C_DrawTextureManager_Bullet();
}
