#include "LaserDraw1.h"


extern LPDIRECT3DDEVICE9		lpD3DDevice;
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


C_LaserDraw1::C_LaserDraw1(const int * TexNo):C_LaserBase2(TexNo)
{
	Draw1Flg = false;
}

void C_LaserDraw1::Draw3DAll(const D3DXMATRIX * Mat, const D3DXVECTOR3 * TransPos, const float * PolSize, const D3DXVECTOR3 * CamPos, const float * Dis, const bool * DrawFlg)
{
	D3DXVECTOR3 StartPos, HitPos;
	GetHitPos(&StartPos, &HitPos, Mat, TransPos, Dis);

	Draw3D_1(&StartPos, &HitPos,CamPos, PolSize, DrawFlg);
}

void C_LaserDraw1::Draw3D_1(const D3DXVECTOR3 * StartPos, const D3DXVECTOR3 * HitPos, const D3DXVECTOR3 * CamPos, const float * PolSize, const bool * DrawFlg)
{
	Draw1Flg = *DrawFlg;
	if (Draw1Flg != true)return;

	//if (m_LaserTex.Tex == nullptr)return;

	for (int p = 0; p < 4; p++) {
		v[p].Color= D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	D3DXVECTOR3 Vec= judg.Billboard(StartPos, HitPos, CamPos, PolSize);
	v[0].Pos = *StartPos + Vec;
	v[1].Pos = *StartPos - Vec;
	v[2].Pos = *HitPos - Vec;
	v[3].Pos = *HitPos + Vec;

	//レーザー作成
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	lpD3DDevice->SetTexture(0, m_LaserTex.Tex);
	D3DXMATRIX Iden;
	D3DXMatrixIdentity(&Iden);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Iden);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
