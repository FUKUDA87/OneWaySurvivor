#include "Hpbar2D.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_Hpbar2D::C_Hpbar2D()
{
	// 白いバー
	hpTex[0] = { NULL,1,1 };
	hpTex[0].Tex = textureManager.GetTexture("HpH.png", hpTex[0].Width, hpTex[0].Height, NULL);
}

void C_Hpbar2D::Draw2D(const int * NowHp, const int * MaxHp)
{
	DrawA(NowHp, MaxHp);
}

void C_Hpbar2D::DrawA(const int * NowHp, const int * MaxHp)
{
	RECT rchp = { 0,0,hpTex[0].Width,hpTex[0].Height };
	D3DXMATRIX tmp, Mat, ScalMat;
	D3DXMatrixTranslation(&Mat, Pos.x, Pos.y, NULL);
	D3DXMatrixScaling(&ScalMat, ScalPos.x, ScalPos.y, NULL);
	tmp = ScalMat * Mat;
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(hpTex[0].Tex, &rchp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(20, 255, 255, 255));

	RECT rcHp = { 0,0,hpTex[1].Width,hpTex[1].Height };
	D3DXMatrixScaling(&ScalMat, ScalPos.x*GetGage(NowHp, MaxHp), ScalPos.y, NULL);
	tmp = ScalMat * Mat;
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(hpTex[1].Tex, &rcHp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
