#include "DrawTextureManager_Bullet.h"

TEXTURE C_DrawTextureManager_Bullet::Get_Texture(const int * TexNo)
{
	if (*TexNo == 1)return Texture_Load("Bullet1-1-1.png", 100, 100);


	return Texture_Load("Bullet1-1-1.png", 100, 100);
}


