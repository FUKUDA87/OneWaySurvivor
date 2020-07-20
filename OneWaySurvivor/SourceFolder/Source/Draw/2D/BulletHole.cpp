#include "BulletHole.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_BulletHole::C_BulletHole(const D3DXVECTOR2 * Pos, const float * AngZ, const D3DXVECTOR2 * ScalPos)
{
	InitBulHol();

	BulHol.Base.ScaPos = *ScalPos;
	BulHol.Base.AngZ = *AngZ;
	BulHol.Base.Pos = *Pos;

	judg.setTransMat(&BulHol.Base.Mat, &BulHol.Base.Pos);
	D3DXMatrixRotationZ(&BulHol.Base.RotZ, D3DXToRadian(BulHol.Base.AngZ));
	BulHol.Base.Mat = BulHol.Base.RotZ*BulHol.Base.Mat;
}

C_BulletHole::C_BulletHole(const D3DXVECTOR2 * Pos, const float * AngZ, const D3DXVECTOR2 * ScalPos, int No)
{
	InitBulHol(No);

	BulHol.Base.ScaPos = *ScalPos;
	BulHol.Base.AngZ = *AngZ;
	BulHol.Base.Pos = *Pos;

	judg.setTransMat(&BulHol.Base.Mat, &BulHol.Base.Pos);
	D3DXMatrixRotationZ(&BulHol.Base.RotZ, D3DXToRadian(BulHol.Base.AngZ));
	BulHol.Base.Mat = BulHol.Base.RotZ*BulHol.Base.Mat;
}

void C_BulletHole::InitBulHol(void)
{
	BulHol.TEX = { NULL,256,256 };
	BulHol.TEX.Tex = textureManager.GetTexture("BulletHole01.png", BulHol.TEX.Width, BulHol.TEX.Height, NULL);
}

void C_BulletHole::InitBulHol(int No)
{
	BulHol.TEX = { NULL,256,256 };
	if (No == 1) {
		BulHol.TEX.Tex = textureManager.GetTexture("BulletHole01.png", BulHol.TEX.Width, BulHol.TEX.Height, NULL);
	}
	else {
		BulHol.TEX.Tex = textureManager.GetTexture("BulletHole02.png", BulHol.TEX.Width, BulHol.TEX.Height, NULL);
	}
}

void C_BulletHole::Draw2DBH(void)
{
	RECT rcBH = { 0,0,BulHol.TEX.Width, BulHol.TEX.Height };
	lpSprite->SetTransform(&GetDrawMatBulHol());
	lpSprite->Draw(BulHol.TEX.Tex, &rcBH, &D3DXVECTOR3((float)BulHol.TEX.Width / 2.0f, (float)BulHol.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
}

D3DXMATRIX C_BulletHole::GetDrawMatBulHol(void)
{
	judg.setScalingMat(&BulHol.Base.Scal, &BulHol.Base.ScaPos);
	return BulHol.Base.Scal*BulHol.Base.Mat;
}

