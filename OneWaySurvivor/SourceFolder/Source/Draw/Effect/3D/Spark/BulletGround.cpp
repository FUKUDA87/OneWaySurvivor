#include "BulletGround.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../MaterialManager/XfileManager.h"
#include"../../../../GameSource/Judgment.h"

extern XFileManager xfileManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
void DrawMesh(XFILE *XFile);

C_BulGro::C_BulGro(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos):C_Spark(Mat,Pos)
{
	InitBG();
	//位置の初期化
	Smoke.Base.Pos = *Pos;

	for (int s = 0; s < SmokeNum; s++) {
		SmokeS[s].Base.Pos = *Pos;
	}

	for (int a = 0; a < AspNum; a++) {
		AspMat[a].Pos = *Pos;
	}
}

C_BulGro::~C_BulGro()
{
	if (AspMat != nullptr) {
		delete[] AspMat;
	}
}

void C_BulGro::InitBG(void)
{
	//画像のロード
	Smoke.Tex = textureManager.GetTexture("Smoke02.png", 32, 32, NULL);

	//
	D3DXMatrixIdentity(&Smoke.Base.Mat);

	//代入
	SmokeNum = 2;
	for (int s = 0; s < SmokeNum; s++) {
		SmokeS[s] = Smoke;
	}

	Smoke.Base.TraPos = D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	NowCount = 4;

	//煙サイドの初期化
	for (int s = 0; s < SmokeNum; s++) {
		SmokeS[s].Base.TraPos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	}

	//破片の初期化
	//メッシュのロード
	AspMesh=xfileManager.GetMesh("AsphaltParts2-2.x");
	//破片の数の初期化
	AspNum = 5;
	AspMat = new BASE3D[AspNum];
	for (int a = 0; a < AspNum; a++) {
		//移動方向の初期化
		AspMat[a].TraPos.x = (float)(rand() % (10+10) -10) / 100.0f;
		AspMat[a].TraPos.y = (float)(rand() % 5+2) / 10.0f;
		AspMat[a].TraPos.z = (float)(rand() % (10 + 10) - 10) / 100.0f;

		//拡大行列の初期化
		AspMat[a].ScaPos = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
		Judg judg;
		judg.setScalingMat(&AspMat[a].Scal, &AspMat[a].ScaPos);
	}
	
	//薄れの初期化
	NowAlpha = 100;
	AlphaDown = 100/3;

	SmoUpY = 0.4f;

	ScaSmo = 1.0f;
}

bool C_BulGro::Update(void)
{
	return CountUpdate();
}

void C_BulGro::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	//煙２のための横幅Vec
	D3DXVECTOR3 sVec;

	//煙昇の表示
	if (1) {
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
		for (int c = 0; c < 4; c++) {
			Smoke.v[c].Color = D3DCOLOR_ARGB(NowAlpha, 100, 100, 100);
		}
		lpD3DDevice->SetTexture(0, Smoke.Tex);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &Smoke.Base.Mat);
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		oPos = Smoke.Base.Pos;
		nPos = Smoke.Base.Pos + Smoke.Base.TraPos*SmoUpY;
		float L_Size = 0.3f;
		Judg judg;
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &L_Size);
		sVec = vec;
		Smoke.v[0].Pos = nPos - vec;
		Smoke.v[1].Pos = nPos + vec;
		Smoke.v[2].Pos = oPos + vec * ScaSmo;
		Smoke.v[3].Pos = oPos - vec * ScaSmo;
		Smoke.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
		Smoke.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
		Smoke.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
		Smoke.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Smoke.v, sizeof(VERTEX));//2はポリゴン数
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	//煙サイドの表示
	if (1) {
		lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
		D3DXVec3Normalize(&sVec, &sVec);
		sVec *= 0.7f;
		sVec *= SmoUpY;
		for (int s = 0; s < SmokeNum; s++) {

			for (int c = 0; c < 4; c++) {
				SmokeS[s].v[c].Color = D3DCOLOR_ARGB(NowAlpha-50, 100, 100, 100);
			}
			lpD3DDevice->SetTexture(0, SmokeS[s].Tex);
			lpD3DDevice->SetTransform(D3DTS_WORLD, &SmokeS[s].Base.Mat);
			//ビルボード
			D3DXVECTOR3 vec, oPos, nPos;
			oPos = SmokeS[s].Base.Pos;
			nPos = oPos;
			nPos.y += SmokeS[s].Base.TraPos.y*0.5f;
			if (s == 0) {
				vec = sVec;
				SmokeS[s].v[1].Pos = nPos;
				SmokeS[s].v[2].Pos = oPos;
				SmokeS[s].v[0].Pos = SmokeS[s].v[3].Pos = oPos - vec;
				SmokeS[s].v[0].Pos.y += SmokeS[s].Base.TraPos.y * SmoUpY;
			}
			else {
				vec = -sVec;
				SmokeS[s].v[1].Pos = nPos;
				SmokeS[s].v[2].Pos = oPos;
				SmokeS[s].v[0].Pos = SmokeS[s].v[3].Pos = oPos - vec;
				SmokeS[s].v[0].Pos.y += SmokeS[s].Base.TraPos.y * SmoUpY;
			}

			SmokeS[s].v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
			SmokeS[s].v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
			SmokeS[s].v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
			SmokeS[s].v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
			lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, SmokeS[s].v, sizeof(VERTEX));//2はポリゴン数
		}
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	
	//破片の表示
	if (1) {
		for (int a = 0; a < AspNum; a++) {
			//移動処理
			AspMat[a].Pos += AspMat[a].TraPos;
			AspMat[a].TraPos.y -= 0.05f;
			D3DXMatrixTranslation(&AspMat[a].Mat, AspMat[a].Pos.x, AspMat[a].Pos.y, AspMat[a].Pos.z);
			//表示処理
			D3DXMATRIX Tmp;
			Tmp = AspMat[a].Scal*AspMat[a].Mat;
			lpD3DDevice->SetTransform(D3DTS_WORLD, &Tmp);
			DrawMesh(&AspMesh);
		}

	}

	//薄れ処理
	NowAlpha += AlphaDown;

	SmoUpY += 0.3f;
	if (SmoUpY > 1.0f)SmoUpY = 1.0f;
}
