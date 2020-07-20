#include "SparkBase.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_SparkBase::C_SparkBase()
{
	count = new C_CountBase(0);

	updateStartFlg = false;
}

C_SparkBase::~C_SparkBase()
{
	if (count != nullptr)delete count;
	if (PolMat != nullptr)delete[] PolMat;
}

bool C_SparkBase::Update(void)
{
	if (updateStartFlg == false)return true;

	//上移動と後ろ移動
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
	Mat = Tmp * Mat;

	Mat._42 += yUp;

	//ジャンプ処理
	UpdateMoveY();

	//行列の更新
	for (int i = PolNum - 1; i > 0; i--)PolMat[i] = PolMat[i - 1];
	PolMat[0] = Mat;

	if (count != nullptr)return count->Update();

	return false;
}

void C_SparkBase::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	if (updateStartFlg == false)updateStartFlg = true;

	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, Tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	for (int i = 0; i < PolNum - 1; i++)
	{
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		Judg judg;
		judg.SetPosM(&nPos, &PolMat[i]);
		judg.SetPosM(&oPos, &PolMat[i + 1]);
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &PolSize);
		v[0].Pos = nPos - vec;
		v[1].Pos = nPos + vec;
		v[2].Pos = oPos + vec;
		v[3].Pos = oPos - vec;
		v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(PolNum - 1));
		v[1].Tex = D3DXVECTOR2(1.0f, (float)i / (float)(PolNum - 1));
		v[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (float)(PolNum - 1));
		v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(PolNum - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void C_SparkBase::UpdateMoveY(void)
{
	if (yUp < -0.001f) {
		yUp += yDown * 0.15f;
	}
	else {
		yUp += yDown;
	}
	/*if (yUp > 0.0f) {
		yUp += yDown;
	}
	else {
		yUp += yDown * 0.5f;
	}*/
}
