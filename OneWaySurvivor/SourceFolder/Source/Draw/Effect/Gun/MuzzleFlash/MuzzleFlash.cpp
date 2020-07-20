#include "MuzzleFlash.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

extern LPDIRECT3DDEVICE9 lpD3DDevice;

c_MuzzleFlash::c_MuzzleFlash(const D3DXMATRIX * Gun_Mouth_Mat)
{
	mat = *Gun_Mouth_Mat;
	D3DXMATRIX RotZ;
	int Ang = rand() % 3600;
	float AngZ = (float)Ang / 10.0f;
	D3DXMatrixRotationZ(&RotZ, D3DXToRadian(AngZ));
	mat = RotZ * mat;

	tex.Width = 128;
	tex.Height = 128;
	tex.Tex = textureManager.GetTexture("MuzFla1T.png", tex.Width, tex.Height, NULL);

	for (int p = 0; p < 4; p++) {
		v[p].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	v[3].Tex = D3DXVECTOR2(0.0f, 1.0f); 
	D3DXVECTOR3 Pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	Pos *= 0.25f;
	v[0].Pos = D3DXVECTOR3(-Pos.x, Pos.y, Pos.z);
	v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);
	v[2].Pos = D3DXVECTOR3(Pos.x, -Pos.y, Pos.z);
	v[3].Pos = D3DXVECTOR3(-Pos.x, -Pos.y, Pos.z);


	AliveFlg = true;
}

bool c_MuzzleFlash::Update(const s_CarEffectUpdateData * updateData)
{
	return AliveFlg;
}

void c_MuzzleFlash::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, tex.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	AliveFlg = false;
}
