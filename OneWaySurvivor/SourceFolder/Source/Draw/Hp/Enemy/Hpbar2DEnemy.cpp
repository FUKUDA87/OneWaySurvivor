#include "Hpbar2DEnemy.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

c_Hpbar2DEnemy::c_Hpbar2DEnemy()
{
	Pos = D3DXVECTOR2(1280.0f / 2.0f, 720.0f*0.1f);
	ScalPos = D3DXVECTOR2(800.0f, 30.0f);
	Pos = GetTexPos(&D3DXVECTOR2((float)hpTex[0].Width, (float)hpTex[0].Height), &Pos, &ScalPos);

	//óŒÉoÅ[
	hpTex[1] = { NULL,1,1};
	hpTex[1].Tex = textureManager.GetTexture("enemyHp.png", hpTex[1].Width, hpTex[1].Height, NULL);
}
