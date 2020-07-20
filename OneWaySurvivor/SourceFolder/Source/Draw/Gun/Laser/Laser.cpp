#include "Laser.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

void LaserA::Init()
{
	lasS.Base.Flg = true;
	lasS.Tex = textureManager.GetTexture("Laser1T.png", 32, 32, NULL);
	Las.Base.Flg = true;
	Las.Tex = textureManager.GetTexture("enemyHp.png", 1, 1, NULL);
	lasFlg = false;
}

D3DXVECTOR3 LaserA::GetLasVec()
{
	D3DXVECTOR3 pos, Pos;
	D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Las.Base.Mat);
	Pos = D3DXVECTOR3(Las.Base.Mat._41, Las.Base.Mat._42, Las.Base.Mat._43);
	pos = pos - Pos;
	D3DXVec3Normalize(&pos, &pos);
	vec = pos;
	return pos;
}

bool LaserA::UpdateS(D3DXMATRIX Mat, D3DXMATRIX tmp)
{
	//レーザーの始点
	lasS.Base.Mat = tmp * Mat;
	lasS.Base.Pos = D3DXVECTOR3(0.05f, 0.05f, 0.0);
	lasS.v[0].Pos = D3DXVECTOR3(-lasS.Base.Pos.x, lasS.Base.Pos.y, 0.0f);//x,y,z
	lasS.v[1].Pos = D3DXVECTOR3(lasS.Base.Pos.x, lasS.Base.Pos.y, 0.0f);
	lasS.v[2].Pos = D3DXVECTOR3(lasS.Base.Pos.x, -lasS.Base.Pos.y, 0.0f);
	lasS.v[3].Pos = D3DXVECTOR3(-lasS.Base.Pos.x, -lasS.Base.Pos.y, 0.0f);

	for (int i = 0; i < 4; i++) {
		lasS.v[i].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	lasS.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	lasS.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	lasS.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	lasS.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	Las.Base.Mat = lasS.Base.Mat;

	return true;
}

bool LaserA::UpdateL(float Dis, bool Flg)
{
	if (Flg == true) {
		D3DXVECTOR3 lpos, pos;

		lpos = D3DXVECTOR3(Las.Base.Mat._41, Las.Base.Mat._42, Las.Base.Mat._43);
		pos = lpos + vec * Dis;
		float lea;
		vec = vec * Dis;
		lea = D3DXVec3Length(&vec);
		pos.z = pos.z - lpos.z;
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, lea);
		lasE.Base.Mat = Tmp * Las.Base.Mat;
	}
	else {
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, LasDis);
		lasE.Base.Mat = Tmp * Las.Base.Mat;
	}
	for (int l = 0; l < 4; l++) {
		Las.v[l].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	Las.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	Las.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	Las.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	Las.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	return true;
}

void LaserA::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	if (lasFlg == true) {
		if (lasS.Base.Flg == true) {
			lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			lpD3DDevice->SetTexture(0, lasS.Tex);
			lpD3DDevice->SetTransform(D3DTS_WORLD, &lasS.Base.Mat);
			lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
			lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, lasS.v, sizeof(VERTEX));//2はポリゴン数
			lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
		if (Las.Base.Flg == true) {
			//レーザー作成
			lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			lpD3DDevice->SetTexture(0, Las.Tex);
			D3DXMATRIX Iden;
			D3DXMatrixIdentity(&Iden);
			lpD3DDevice->SetTransform(D3DTS_WORLD, &Iden);
			lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
			//ビルボード
			D3DXVECTOR3 vec, LPos, EPos;
			Judg judg;
			judg.SetPosM(&LPos, &Las.Base.Mat);
			judg.SetPosM(&EPos, &lasE.Base.Mat);
			float L_Size = 0.01f;
			vec = judg.Billboard(&LPos, &EPos, CameraPos,&L_Size);
			Las.v[0].Pos = LPos + vec;
			Las.v[1].Pos = LPos - vec;
			Las.v[2].Pos = EPos - vec;
			Las.v[3].Pos = EPos + vec;
			lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Las.v, sizeof(VERTEX));//2はポリゴン数
			lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

