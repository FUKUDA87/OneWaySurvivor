#include "Hpbar3DEnemy.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

c_Hpbar3DEnemy::c_Hpbar3DEnemy()
{
	yUp = 1.5f;

	ScalPos = D3DXVECTOR2(0.7f, 0.1f);

	hpTex = textureManager.GetTexture("HpE5.png", 200, 100, NULL);
}
