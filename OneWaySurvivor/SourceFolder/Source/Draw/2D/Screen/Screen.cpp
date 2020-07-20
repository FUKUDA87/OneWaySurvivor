#include "Screen.h"
#include"../../../GameSource/Judgment.h"
#include"../../../Key/Key.h"

extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

c_Screen::c_Screen()
{
	// ミニ画面の初期化
	DrawFlg = false;
	lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpBackBuffer);
	lpD3DDevice->GetDepthStencilSurface(&lpZBuffer);//DepthStencilSurface=Zバッファ
	D3DXCreateTexture(lpD3DDevice, 2048, 1024, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &lpTmpTex);//X=2048,Y=1024,裏バックバッファを２のべき乗サイズ
	lpTmpTex->GetSurfaceLevel(0, &lpTmpBackBuffer);
	lpD3DDevice->CreateDepthStencilSurface(2048, 1024, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &lpTmpZBuffer, NULL);
}

c_Screen::~c_Screen()
{
	lpBackBuffer->Release();
	lpZBuffer->Release();
	lpTmpBackBuffer->Release();
	lpTmpZBuffer->Release();
	lpTmpTex->Release();
}

bool c_Screen::Update(const bool * KeyFlg)
{
	Judg judg;

	// ミニ画面の表示変更
	if (*KeyFlg==true)judg.ReverseFlg(&DrawFlg);

	return true;
}

void c_Screen::Draw2D(void)
{
	// ミニ画面の表示
	if (DrawFlg != true)return;
	
	RECT rcTmp = { 0,0,1280,720 };
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, NULL);
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(lpTmpTex, &rcTmp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//２５５～１０残像ができる
}

bool c_Screen::RenderStart(const D3DXMATRIX *Mat)
{
	if (DrawFlg != true)return false;

	lpD3DDevice->SetRenderTarget(0, lpTmpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(lpTmpZBuffer);
	D3DVIEWPORT9 Viewport;
	Viewport.X = 0;
	Viewport.Y = 0;
	Viewport.Width = 1280 / 2;
	Viewport.Height = 720 / 2;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	lpD3DDevice->SetViewport(&Viewport);
	// バックバッファと Z バッファをクリア
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//    バックバッファ　　　Zバックバッファ

	D3DXMATRIX mView, mProj;

	// カメラの位置の行列作成
	D3DXMATRIX CamMat;
	D3DXMatrixTranslation(&CamMat, 45.0f, 50.0f, -1.0f);
	CamMat = CamMat * (*Mat);

	Judg judg;

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&judg.SetPosM(&CamMat),	// カメラの位置
		&judg.SetPosM(Mat),	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	// 行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	// この後にRender3D

	return true;
}

void c_Screen::RenderEnd(void)
{
	// この前にRender3D
	lpD3DDevice->SetRenderTarget(0, lpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(lpZBuffer);
}
