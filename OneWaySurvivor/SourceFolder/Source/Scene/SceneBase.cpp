#include"SceneBase.h"
extern LPDIRECT3DDEVICE9 lpD3DDevice;
void SceneBase::Frame(void)
{
	//60FPS計算
	NowTime = timeGetTime();
	if ((NowTime - PrevTime0) < (1000 / 60)) {
		return;
	}
	else {
		PrevTime0 = NowTime;
	}
	if ((NowTime - PrevTime) >= 1000) {
		PrevTime = NowTime;
		Fps = Cnt;
		Cnt = 0;
	}
	Cnt++;

	if (Update() == false) {
		return;
	}
	// 描画開始
	lpD3DDevice->BeginScene();
	// バックバッファと Z バッファをクリア
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	SetCamera();
	Render3D();

	Render3DScreen();

	// 2D描画
	Render2D();



	// 描画終了
	lpD3DDevice->EndScene();

	// バックバッファをプライマリバッファにコピー
	lpD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void SceneBase::Render3D(void)
{
	/*派生クラス側でオーバーライドしなかったときに空っぽの関数を作っておく*/
}
void SceneBase::Render3DScreen(void)
{
}
void SceneBase::Render2D(void)
{
	/*派生クラス側でオーバーライドしなかったときに空っぽの関数を作っておく*/
}
void SceneBase::SetCamera(void)
{
	/*派生クラス側でオーバーライドしなかったときに空っぽの関数を作っておく*/
}
bool  SceneBase::Update(void) {
	return true;
}
SceneBase::~SceneBase()
{

}