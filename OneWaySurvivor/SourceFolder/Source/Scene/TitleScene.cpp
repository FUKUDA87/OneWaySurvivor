#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"StageSelectScene.h"
#include"../Fade/Fade.h"

extern TextureManager textureManager;
extern XFileManager xfileManager;
extern LPD3DXSPRITE lpSprite;	// スプライト
extern SceneManager sceneManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern C_Fade fade;
extern C_Option option;

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
#define StageSelectNo 1

void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


TitleScene::TitleScene()
{
	
	// フェードインの開始
	fade.StartFadein();

	//プレイヤーの初期化の前に初期化
	PlaBodData = new C_PlayerBody();

	player = new C_PlayerA(&PlaBodData->GetPData());
	//地面初期化--------------------------------------------------------
	
	groundManager = new c_GroundManager(player);

	//---------------------------------------------------------------------
	//マウスの初期化
	mouse = new C_Mouse();
	mouse->ChaDrawFlg(true);

	titleTex = new TitleTex();
	startTex = new StartTex();

	camera = new TitleCamera();
	sky = new Sky();

	key.Init();

	//サウンドの初期化
	int BGMVolume = option.GetOptionData().BGMVolume, SEVolume = option.GetOptionData().SEVolume;
	M_C_Sound_Manager = new c_GameSoundManager(&BGMVolume, &SEVolume);

	//弾痕の初期化
	if (false) {
		float AngZ = -90.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(250.0f, 720.0f / 4.0f*3.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(250.0f, 720.0f / 4.0f*3.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 2));
		AngZ = (70.0f)*-1.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(1050.0f, 500.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 1));
		AngZ += 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(990.0f, 380.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 1));
		AngZ -= 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(1050.0f, 500.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 2));
		AngZ += 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(990.0f, 380.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 2));
		AngZ = -0.0f;
		//BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(455.0f, 85.0f, 0.0f), &AngZ, &D3DXVECTOR3(1.2f, 1.2f, 1.0f)));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(300.0f, 200.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(300.0f, 200.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 2));

		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(1100.0f, 100.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR2(1100.0f, 100.0f), &AngZ, &D3DXVECTOR2(2.1f, 2.1f), 2));
	}

	int No = 2;
	M_C_Sound_Manager->BGMStart(&No);

}
TitleScene::~TitleScene()
{

	delete player;
	delete titleTex;
	delete startTex;
	delete camera;
	delete sky;
	//地面の削除
	if (groundManager != nullptr)delete groundManager;
	//弾痕削除
	if (BulHol.size() > 0) {
		for (unsigned int b = 0; b < BulHol.size(); b++) {
			delete BulHol[b];
			BulHol.erase(BulHol.begin() + b);
			b--;
		}
	}
	//マウスの削除
	delete mouse;

	delete PlaBodData;

	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Reset();
		delete M_C_Sound_Manager;
	}

}
bool TitleScene::Update(void)
{

	if (M_C_Sound_Manager != nullptr) {

		S_OptionData l_OptionData = option.GetOptionData();

		M_C_Sound_Manager->UpdateVolume(&l_OptionData.BGMVolume, &l_OptionData.SEVolume);

		M_C_Sound_Manager->Update();

		M_C_Sound_Manager->New();

	}

	Game_End();

	//bgmのアップデート
	bool bFlg = true;
	SoundCamera scB;
	scB.CamPos = camera->GetPos();
	scB.CamLook = camera->GetLook();
	scB.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	mouse->Update();

	//フェードのアップデート
	if (fade.Update() == true) {
		//キーの無力化

	}
	else {
		// フェードアウトが完了した時
		if (fade.GetMoveEndFlg() == true) {
			sceneManager.changeScene(new StageSelectScene());
			return false;
		}
	}

	//ステージ選択シーンへ移動
	Next_StageScene_Switch();

	//================================================================================
	//地面
	//================================================================================
	if (groundManager != nullptr)groundManager->Update(player);
	// プレイヤーと地面判定
	float Dis;
	unsigned int num;
	if (groundManager->JudgNowGround(&num, &Dis,nullptr, &player->GetMatCar()) == true) {
		player->SetGroNum(&num);//地面の取得
	}
	player->UpdateCarFM(groundManager->GetGround());
	
	player->Update();
	camera->Update(player->GetMatCar());
	sky->Update(&player->GetMatCar());

	
	return true;
}

void TitleScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//titleTexの表示
	titleTex->Draw();

	startTex->DrawSu();

	fade.Draw();

	//弾痕表示
	if (BulHol.size() > 0) {
		for (unsigned int b = 0; b < BulHol.size(); b++) {
			BulHol[b]->Draw2DBH();
		}
	}
	

	mouse->Draw2D();
	// 描画終了
	lpSprite->End();
}

void TitleScene::Render3D(void)
{
	if (groundManager != nullptr)groundManager->Draw3D();
	player->Draw3D(&camera->GetPos());
	sky->Draw();
}

void TitleScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&camera->GetPos(),//カメラの位置
		&camera->GetLook(),// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 1200.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

}

bool TitleScene::Game_End(void)
{
	if (key.EscapeKey_F() == true) {
		PostQuitMessage(0);
		return false;
	}
	return true;
}

void TitleScene::Next_StageScene_Switch(void)
{
	//スイッチの更新と動作の確認
	if (startTex->UpdateSu() != false) return;

	//マウスカーソルを手にする処理
	mouse->SetTouchFlg();

	//スイッチが動作中かの確認
	if (startTex->GetMoveFlg() != false)return;

	//シーン切り替え状態であるかの確認
	if (fade.GetMoveFlg() != false) return;

	//クリックしたかの確認
	if (key.LClickF() != true) return;

	//スイッチの動作開始
	startTex->SetMoveFlg(true);

	//フェードアウトの開始
	fade.StartFadeout();

	//BGMの削除
	M_C_Sound_Manager->BGMDelete();

	//クリック音
	M_C_Sound_Manager->New_Sound_Data(&Co_Sound_Type_2D, &Co_Sound_Category_Click, 1, &Co_SoundNew);
}
