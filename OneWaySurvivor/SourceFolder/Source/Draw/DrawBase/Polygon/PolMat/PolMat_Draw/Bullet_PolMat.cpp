#include "Bullet_PolMat.h"
#include"../../../../../GameSource/Judgment.h"

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

C_Bullet_PolMat::C_Bullet_PolMat(const int * BulletTexNo, const float * PolSize, const int * PolNum)
{
	Init_Draw();

	float p = *PolSize;
	if (p < 0.0f)p = 1.0f;
	M_PolSize->Set(&p);

	int n = *PolNum;
	if (n < 1)n = 2;
	Init_PolMat(n);
}

C_Bullet_PolMat::~C_Bullet_PolMat()
{
	Delete_Draw();
}

void C_Bullet_PolMat::DrawBase(const D3DXVECTOR3 *CameraPos)
{
	if (PolMat_Judg((M_PolNumLine->Get())) != true)return;

	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	
	int Alpha = 255;
	Pol_SetAllColor(&Alpha);

	lpD3DDevice->SetTexture(0, Get_S_Texture().Tex);

	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

	for (int i = 0; i < (Get_PolMatNum() - 1); i++) {
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		Judg judg;

		judg.SetPosM(&nPos, &M_Polygon.Mat[i]);
		judg.SetPosM(&oPos, &M_Polygon.Mat[i + 1]);
		float L_Size = M_PolSize->Get();
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &L_Size);
		
		v[0].Pos = nPos - vec;
		v[1].Pos = nPos + vec;
		v[2].Pos = oPos + vec;
		v[3].Pos = oPos - vec;

		v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(Get_PolMatNum() - 1));
		v[1].Tex = D3DXVECTOR2(1.0f, (float)i / (float)(Get_PolMatNum() - 1));
		v[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (float)(Get_PolMatNum() - 1));
		v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(Get_PolMatNum() - 1));
		//表示
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数
	}

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void C_Bullet_PolMat::Init_Draw(void)
{
	int i = 2;
	M_PolNumLine = new C_Int(&i);

	M_PolSize = new C_Float();
}

void C_Bullet_PolMat::Delete_Draw(void)
{
	if (M_PolNumLine != nullptr) {
		delete M_PolNumLine;
	}

	if (M_PolSize != nullptr) {
		delete M_PolSize;
	}
}
