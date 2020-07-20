#include "Hpbar3D.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Hpbar3D::C_Hpbar3D()
{
	Init();
}

void C_Hpbar3D::Draw3D(const int * NowHp, const int * MaxHp
	, const D3DXMATRIX * Mat, const D3DXVECTOR3 * CamPos
	, const D3DXVECTOR3 *CharaScalPos)
{
	if (*NowHp <= 0)return;

	if ((drawFlg == false) && (*NowHp < *MaxHp)) {
		drawFlg = true;
	}

	if (drawFlg != true)return;

	for (int p = 0; p < 4; p++) {
		v[p].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	float Per = 0.5f*GetGage(NowHp, MaxHp);
	v[0].Tex = D3DXVECTOR2(0.5f - Per, 0.0f);
	v[1].Tex = D3DXVECTOR2(1.0f - Per, 0.0f);
	v[2].Tex = D3DXVECTOR2(1.0f - Per, 1.0f);
	v[3].Tex = D3DXVECTOR2(0.5f - Per, 1.0f);

	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0.0f, yUp*(CharaScalPos->y), 0.0f);
	TmpMat = TmpMat * (*Mat);
	Judg judg;
	D3DXVECTOR3 PosS, PosE, vec;
	judg.SetPosM(&PosS, &TmpMat);
	PosE = PosS;
	PosS.y += ScalPos.y;
	PosE.y -= ScalPos.y;
	vec = judg.Billboard(&PosS, &PosE, CamPos, &ScalPos.x);
	v[0].Pos = PosS + vec;
	v[1].Pos = PosS - vec;
	v[2].Pos = PosE - vec;
	v[3].Pos = PosE + vec;

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, hpTex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void C_Hpbar3D::Init(void)
{
	drawFlg = false;
}
