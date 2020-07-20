#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelectScene.h"
#include"SceneManager.h"
#include"../GameSource/Enum.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"../GameSource/Motion.h"
#include"../Car/Data/Draw3DManager/CarSmogManager.h"
#include"../Enemy/Data/Base&Manager/Enemy_Manager.h"
#include"../Const/Const_Wave_Type.h"
#include"../Const/Const_Rail_Type.h"
#include"../Const/Const_Stage_Type.h"
#include"../GameSource/StructClass/Struct_Init.h"
#include"../Draw/Gun/Bullet/Const_Bullet_No.h"
#include"../Fade/Fade.h"
#include"../Draw/Effect/3D/BulletHole/BulletHole3D.h"
#include"../Draw/Effect/3D/Explosion/Explosion3D.h"
#include"../Draw/Effect/3D/Spark/SparkDamege.h"
#include"../Draw/Effect/3D/Spark/BulletGround.h"
#include"../GameSource/StructManager.h"
#include"../Draw/Effect/3D/Spark/CarSideHitSpark.h"
#include"../Draw/Effect/3D/Spark/WallSideHitSpark.h"

extern int CountManager;
extern Motion motion;
extern TextureManager textureManager;
extern XFileManager xfileManager;
extern SceneManager sceneManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern LPD3DXSPRITE lpSprite;	// スプライト
extern LPD3DXFONT lpFont;		// フォント
extern C_Fade fade;
extern C_Option option;

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
#define RadJudgF 100
#define StageSelectNo 2
#define GameNo 3
#define TitleNo 1

GameScene::GameScene(const int stageNum)
{
	StageNo = stageNum;
	Init();
}
GameScene::GameScene(const int stageNum, const bool * DebugFlg)
{
	StageNo = stageNum;

	if (*DebugFlg == true)StageNo = Co_Stage_Type_Debug;

	Init();

	if (*DebugFlg != true)return;

	if (player != nullptr) {
		unsigned int i = 0;
		player->Set_Gun_Bullet_No(&i, &Co_Bullet_No99);
	}
}
GameScene::~GameScene() 
{
	// ミニ画面の削除
	if (screen != nullptr)delete screen;

	if (textDraw != nullptr)delete textDraw;

	if (groundManager != nullptr)delete groundManager;

	//敵の削除
	if (enemy.size() > 0)
	{
		for (unsigned int ec = 0; ec < enemy.size(); ec++)
		{
			delete enemy[ec];
			enemy.erase(enemy.begin() + ec);
			ec--;
		}
	}
	
	delete player;
	delete sky;
	delete camera;
	delete aiming;
	delete debug;

	if (gameEnd != nullptr) {
		delete gameEnd;
	}

	delete war;
	delete pause;
	delete spear;
	//スコアの削除
	delete score;

	//車の情報を削除
	if (carPop != nullptr) delete carPop;
	

	//マウスの削除
	delete mouse;

	if (effectManager != nullptr)delete effectManager;

	//プレイヤーの情報削除
	delete playerBody;
	

	//音の管理の削除
	if (soundGameManager != nullptr) {
		soundGameManager->Reset();
		delete soundGameManager;
	}

	if (damageNumDraw3DManager != nullptr)delete damageNumDraw3DManager;

	//メニューの削除
	if (Menu != nullptr)delete Menu;

	if (sideSparkData != nullptr)delete sideSparkData;
}
void GameScene::Render3D(void) {
	/*if (player->GetBulSiz() > 0) {
		spear->Draw3DV(player->GetBulMat(0));
	}*/
	sky->Draw();
	
	if (groundManager != nullptr)groundManager->Draw3D();

	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw3D(&camera->GetPos());
		}
	}

	player->Draw3D(&camera->GetPos());

	if (effectManager != nullptr)effectManager->Draw3D(&camera->GetPos());

}
void GameScene::Render3DScreen(void)
{
	if (screen == nullptr)return;

	D3DXMATRIX Mat = player->GetCon().JudgMat;

	if (screen->RenderStart(&Mat) != true)return;

	Render3D();

	screen->RenderEnd();

}
void GameScene::Render2D(void) {
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (damageNumDraw3DManager != nullptr)damageNumDraw3DManager->Draw2D();

	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) enemy[i]->Draw2D();
	}

	aiming->Draw();
	player->Draw2D();

	if (screen != nullptr)screen->Draw2D();

	//スコアの表示
	score->Draw2D();
	//クリアとオーバーの表示
	if (gameEnd != nullptr) gameEnd->Draw_2D();
	//ボス出現表示
	war->Draw2D();

	//ポーズの表示
	pause->Draw();

	//メニューの表示
	if (Menu != nullptr)Menu->Draw2DAll();

	//フェードインアウトの表示
	fade.Draw();
	mouse->Draw2D();
	// 描画終了
	lpSprite->End();

	//デバック用の文字表示
	if (textDraw != nullptr){
		
	}
}
bool GameScene::Update(void) {

	if (key.EscapeKey_F() == true) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}

	/*サウンドの更新処理*/
	if (soundGameManager != nullptr)
	{

		S_OptionData l_OptionData = option.GetOptionData();

		soundGameManager->UpdateVolume(&l_OptionData.BGMVolume, &l_OptionData.SEVolume);

		soundGameManager->Update();

		soundGameManager->New();

		/*/Soundをプレイヤー側で鳴らす*/
		if (player != nullptr) {
			for (unsigned int s = 0; s < player->Get_Sound_Data_Num(); s++) {
				if (soundGameManager->Order(&player->Get_Sound_Data(&s)) == true) {
					player->Delete_Sound(&s);
				}
			}
		}

		if (war != nullptr) {
			for (unsigned int d = 0; d < war->Get_Sound_Data_Num(); d++) {
				if (soundGameManager->Order(&war->Get_Sound_Data(&d)) == true) {
					war->Delete_Sound(&d);
				}
			}
		}

	}

	/*デバッグ処理*/
	/*if (StageNo != Co_Stage_Type_Debug)return true;*/

	//フレーム数の操作

	if (GetAsyncKeyState('2') & 0x8000) {
		MaxCount += 1;
		if (MaxCount > 60)MaxCount = 60;
	}
	if (GetAsyncKeyState('3') & 0x8000) {
		MaxCount -= 1;
		if (MaxCount < 1)MaxCount = 1;
	}

	bool keyFlg = key.Num1_Key_F();
	if (screen != nullptr)screen->Update(&keyFlg);

	if (key.XKeyF() == true)player->SetHP(1);
	
	// マウスの更新処理
	mouse->Update();

	// フェードの更新処理
	if (fade.Update() == true) {
		//キーの無力化
		key.SetFlg(true);
	}
	else {
		if (fade.GetMoveEndFlg() == true) {
			// シーン切り替え
			sceneManager.changeScene(fade.GetNextScene());
			return false;
		}
	}

	UpdateGame();

	//メニューの更新
	UpdateMenu();

	return true;
}

void GameScene::Init(void)
{

	// フェードインの開始
	fade.StartFadein();

	screen = new c_Screen();

	if (textDraw == nullptr)textDraw = new C_Text_Num();

	effectManager = new C_EffectManager();

	//マウスの初期化
	mouse = new C_Mouse();
	mouse->Init();
	mouse->ChaDrawFlg(false);

	//プレイヤーの初期化前に初期化
	playerBody = new C_PlayerBody();

	player = new C_PlayerA(&playerBody->GetPData());

	//地面初期化--------------------------------------------------------

	groundManager = new c_GroundManager(player);
	eneFlg = true;

	//---------------------------------------------------------------------

	//スコアの初期化
	score = new C_Score();
	sky = new Sky();
	camera = new Camera(player->GetMatCar());
	aiming = new Aiming();
	debug = new Debug();
	eneFlg = false;//敵の出現OFF
	gameEnd = new C_Game_End_Now();

	key.Init();

	war = new Warning();

	pause = new Pause();

	damageNumDraw3DManager = new c_DamageNumDraw3DManager();

	//BulletBirthFlgを最初は出ないようにする
	bulletBirthFlg = false;

	//車の出現の初期化
	carPop = new C_Car_Pop_New(&StageNo);

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);

	//サウンドの初期化
	int BGMVolume = option.GetOptionData().BGMVolume, SEVolume = option.GetOptionData().SEVolume;
	soundGameManager = new c_GameSoundManager(&BGMVolume, &SEVolume);

	int No = 1;
	soundGameManager->BGMStart(&No);

	sideSparkData = new C_SideSparkData();
}

bool GameScene::UpdateEnemy(void)
{
	//=======================================================================================================================
	//エネミーUpdate
	//=======================================================================================================================

	if (enemy.size() > 0) {
		//地面判定2
		for (unsigned int e = 0; e < enemy.size(); e++) {

			if (enemy[e]->GetFlgCar() != true) continue;

			//enemyと地面判定
			unsigned int num;
			float dis;
			if (groundManager->JudgNowGround(&num, &dis, nullptr, &enemy[e]->GetMatCar()) == true) {
				enemy[e]->SetGroNum(&num);
			}
			else {
				delete enemy[e];
				enemy.erase(enemy.begin() + e);
				e--;
			}
			
		}

		for (unsigned int e = 0; e < enemy.size(); e++) EnemyDelete(&e);
		
		for (unsigned int i = 0; i < enemy.size(); i++) {

			if (enemy[i]->GetDeleFlg() != false)continue;

			float L_Radius = 400.0f;

			if (judg.BallJudg(&judg.SetPosM(&enemy[i]->GetMatCar()), &judg.SetPosM(&player->GetMatCar()), &L_Radius) != false) continue;

			delete enemy[i];
			enemy.erase(enemy.begin() + i);
			i--;
			
		}
	}
	if (GetEndFlg() == true) {
		return true;
	}

	return true;
}
void GameScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&camera->GetPos(),//カメラの位置
		&camera->GetLook(),// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);


	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	//Pos2Dのした準備
	D3DVIEWPORT9 Viewport;
	lpD3DDevice->GetViewport(&Viewport);
	//Pos2Dを使う
	Pos2DUpdate(&mProj, &mView, &Viewport);

	FrustumCulling(&mProj, &mView, &Viewport);

}

void GameScene::SideJudg()
{
	if (groundManager == nullptr)return;

	if (groundManager->GetGroundNum() <= 0)return;

	for (unsigned int gc = 0; gc < groundManager->GetGroundNum(); gc++)
	{
		if (groundManager->GetWallNum(&gc) <= 0)continue;

		for (unsigned int wc = 0; wc < groundManager->GetWallNum(&gc); wc++)
		{
			float X = 1.0f;
			if (wc > 0)X *= -1.0f;
			SideJudg(&Hit_Type_Wall, &gc, &wc, &X);
		}
	}

	// プレイヤーの横移動処理
	UpdatePlayerXTrans();

	// 火花出現処理
	if (sideSparkData->getDataNum() > 0)
	{
		for (unsigned int sc = 0; sc < sideSparkData->getDataNum(); sc++)
		{
			S_SideSparkData data = sideSparkData->getData(&sc);

			// ダメージ
			if (data.type[1].Type == Hit_Type_Enemy)
			{
				enemy[data.type[1].Numbar[0]]->SetHP(1, true);
			}

			// 火花
			if ((data.type[1].Type == Hit_Type_Player) || (data.type[1].Type == Hit_Type_Enemy))
			{
				// 車体の火花出現
				bool InitFlg = false;
				for (int i = 0; i < 15; i++) {
					effectManager->NewEffect(new C_CarSideHitSpark(&data.initMat, &InitFlg));
				}
				InitFlg = true;
				for (int i = 0; i < 12; i++) {
					effectManager->NewEffect(new C_CarSideHitSpark(&data.initMat, &InitFlg));
				}
			}
			else {
				if (data.type[1].Type == Hit_Type_Wall)
				{
					// 壁の火花出現
					bool InitFlg = false, LeftFlg = false;
					if (data.type[1].Numbar[1] == 0)LeftFlg = true;
					for (int i = 0; i < 40; i++) {
						effectManager->NewEffect(new C_WallSideHitSpark(&data.initMat, &InitFlg,&LeftFlg));
					}
					InitFlg = true;
					for (int i = 0; i < 15; i++) {
						effectManager->NewEffect(new C_WallSideHitSpark(&data.initMat, &InitFlg, &LeftFlg));
					}
				}
			}

			// 削除
			sideSparkData->deleteData(&sc);
		}
	}
}

void GameScene::SideJudg(const int * CarType, const unsigned int * No1, const unsigned int * No2, const float * MoveVecX)
{
	bool WallJudgFlg = false;

	c_StructManager structManager;

	s_CarType judgCar = structManager.GetCarType(CarType, No1, No2);

	SideJudg(&WallJudgFlg, &judgCar, MoveVecX, CarType);
}

void GameScene::SideJudg(bool * WallJudgFlg, const s_CarType *carType, const float * MoveVecX, const int *FirstCarType)
{
	bool flg = false, JudgType = false;

	// カプセルの準備
	S_Capsule capsule;
	if (carType->Type == Hit_Type_Player)
	{
		if (player == nullptr)return;
		capsule = player->GetCapsule(&JudgType);
		flg = true;
	}
	else {
		if (carType->Type == Hit_Type_Enemy)
		{
			if ((enemy.size() <= 0) || (carType->Numbar[0] >= enemy.size()))return;
			capsule = enemy[carType->Numbar[0]]->GetCapsule(&JudgType);
			flg = true;
		}
		else {
			if (carType->Type == Hit_Type_Wall)
			{
				if (groundManager == nullptr)return;
				capsule = groundManager->GetCapsuleWall(&carType->Numbar[0], &carType->Numbar[1]);
				flg = true;
			}
		}
	}

	// 準備出来ない場合判定しない
	if (flg == false)return;

	// 次に判定する車の情報
	s_CarType hitCar;
	int hitNum = 0;
	float smallDis;

	// プレイヤー判定
	CapsuleJudgPlayer(&smallDis,&hitNum, &hitCar, &capsule, carType, &flg, &JudgType);

	// 敵判定
	CapsuleJudgEnemy(&smallDis, &hitNum, &hitCar, &capsule, carType, &flg, &JudgType);

	// 壁判定
	if (groundManager != nullptr)groundManager->CapsuleJudgWall(&smallDis, &hitNum, &hitCar, &capsule, carType);

	if (hitNum <= 0)return;

	smallDis += 0.001f;
	float X = *MoveVecX, S = judg.rate(MoveVecX, &smallDis);
	if (S < 0.0f)S *= -1.0f;
	X *= S;

	s_CarType moveCar = hitCar;
	bool reverseFlg = false;

	if (hitCar.Type == Hit_Type_Wall)
	{
		if (*WallJudgFlg == true)
		{
			return;
		}
		else {
			*WallJudgFlg = true;
		}

		X *= -1.0f;
		moveCar = *carType;
		reverseFlg = true;
	}
	else {
		if (hitNum > 1)
		{
			X *= -1.0f;
			moveCar = *carType;
			reverseFlg = true;
		}
	}

	// 当たった車を横移動
	switch (moveCar.Type)
	{
	case Hit_Type_Player:
		player->SetSideTransMat(&X);
		break;
	case Hit_Type_Enemy:
		enemy[moveCar.Numbar[0]]->SetSideTransMat(&X);
		EnemyStop(&moveCar.Numbar[0], FirstCarType);
		break;
	}

	// 判定している車から火花を出す準備
	if (carType->Type == Hit_Type_Player)
	{
		// 火花の初期位置
		if (player != nullptr)
		{
			D3DXMATRIX mat = player->getSparkInitMat(&X, &reverseFlg);
			if (sideSparkData != nullptr)sideSparkData->NewData(carType, &hitCar, &mat, FirstCarType);
		}
	}
	else {
		if (carType->Type == Hit_Type_Enemy)
		{
			// 火花の初期位置
			if ((enemy.size() > 0) && (carType->Numbar[0] < enemy.size()))
			{
				D3DXMATRIX mat = enemy[carType->Numbar[0]]->getSparkInitMat(&X, &reverseFlg);
				if (sideSparkData != nullptr)sideSparkData->NewData(carType, &hitCar, &mat, FirstCarType);
			}
		}
	}

	// 移動した車を判定する
	SideJudg(WallJudgFlg, &moveCar, &X, FirstCarType);

}

bool GameScene::UpdateEnemyAI(void)
{
	//エネミーの出現
	PopEnemy();

	//出現している敵の数がゼロの場合に地面判定をしない
	if (enemy.size() <= 0) return false;

	//地面判定
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//enemyと地面判定
		unsigned int num;
		float dis;
		if (groundManager->JudgNowGround(&num, &dis, nullptr, &enemy[e]->GetMatCar()) == true) {
			enemy[e]->SetGroNum(&num);
		}
		else {
			if (GetEndFlg() == true) {
				delete enemy[e];
				enemy.erase(enemy.begin() + e);
				e--;
			}
		}
	}

	//出現している敵の数がゼロの場合にAIの処理をしない
	if (enemy.size() <= 0) return false;

	/*Aiの動作準備*/

	//プレイヤー側の情報の作成
	CHARAData*Data;
	int ChaNum = 0;
	ChaNum += 1;
	Data = new CHARAData[ChaNum];
	Data[0] = player->GetData();

	/*Aiの動作処理*/

	for (unsigned int i = 0; i < enemy.size(); i++) {

		//全ての戦闘終了Flg
		bool L_EndFlg = GetEndFlg();

		//Aiの動作処理
		enemy[i]->UpdateAi(Data, &ChaNum,&L_EndFlg);

	}

	//情報の削除
	if (Data != nullptr)delete Data;

	return true;
}

bool GameScene::ForMoveJudg(void)
{
	//移動後の変数
	D3DXMATRIX EndMat;
	D3DXVECTOR3 EndPos;

	//移動ベクトルのサイズ
	float Mul;

	//player
	//移動後の行列作成
	ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
	player->SetForMoveEndMat(&EndMat);
	//移動ベクトル計算
	player->SetForMoveVec(&judg.MatMatVec(player->GetMatCar(), player->GetForMoveEndMat()));

	//playerのVecサイズ
	Mul = player->GetQuaForMove().SpeedMulJudg;

	bool L_CollisionJudg_TrueFlg = player->Get_CollisionJudg_TrueFlg();

	// 他の車の行列を正す
	if (enemy.size() > 0)
	{
		for (auto && e : enemy)
		{
			D3DXMATRIX tmp;
			D3DXMatrixTranslation(&tmp, 0.0f, -e->GetQuaForMove().BodyHeight, 0.0f);
			tmp = tmp * e->GetMatCar();
			e->SetForMoveEndMat(&tmp);
		}
	}

	//判定
	ForMoveJudg(&Hit_Type_Player, nullptr,&player->GetForMoveVec(), &Mul, &L_CollisionJudg_TrueFlg);
	//Mulを本体に入れる
	player->SetQuaVecSize(&Mul);
	//移動後の行列作成
	ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
	player->SetForMoveEndMat(&EndMat);


	//enemy
	if (enemy.size() > 0) {//enemyの存在確認
		//enemyの数
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//移動後の行列作成
			ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
			enemy[e]->SetForMoveEndMat(&EndMat);
			//移動ベクトル計算
			enemy[e]->SetForMoveVec(&judg.MatMatVec(enemy[e]->GetMatCar(), enemy[e]->GetForMoveEndMat()));


			if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

			//enemyのVecサイズ
			Mul = enemy[e]->GetQuaForMove().SpeedMulJudg;

			L_CollisionJudg_TrueFlg = enemy[e]->Get_CollisionJudg_TrueFlg();

			//判定
			ForMoveJudg(&Hit_Type_Enemy, &e,&enemy[e]->GetForMoveVec(), &Mul, &L_CollisionJudg_TrueFlg);
			//Mulを本体に入れる
			enemy[e]->SetQuaVecSize(&Mul);
			//移動後の行列作成
			ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
			enemy[e]->SetForMoveEndMat(&EndMat);
		}
	}

	/*当たり判定完了*/

	return true;
}

bool GameScene::ForMoveJudg(const int *CarType, const unsigned int *CarNo
	, const D3DXVECTOR3 *MoveVec, float *SpeedMul2,const bool *CollisionJudg_TrueFlg)
{
	//判定する車の種類
	c_StructManager structManager;

	s_CarType judgCar = structManager.GetCarType(CarType, CarNo);

	S_Capsule capulse;

	bool JudgType = true;

	if (judgCar.Type == Hit_Type_Player)
	{
		capulse = player->GetCapsule(&JudgType);
	}
	else {
		if (judgCar.Type == Hit_Type_Enemy)
		{
			capulse = enemy[judgCar.Numbar[0]]->GetCapsule(&JudgType);
		}
		else {
			return false;
		}
	}

	//レイの長さと最小
	float Dis, SmallDis;

	Dis = D3DXVec3Length(MoveVec);
	if (Dis < 0.0f)Dis *= -1.0f;
	Dis += 0.1f;

	int hitNum = 0;

	s_CarType hitCar;

	//player判定
	CapsuleJudgPlayer(&SmallDis, &hitNum, &hitCar, &capulse, &judgCar, CollisionJudg_TrueFlg, &JudgType);
	
	//敵判定
	CapsuleJudgEnemy(&SmallDis, &hitNum, &hitCar, &capulse, &judgCar, CollisionJudg_TrueFlg, &JudgType);
	
	//レイが当たった
	if (hitNum > 0)
	{
		// 移動量の変更
		float Size = Dis - SmallDis;
		Dis = Size / Dis;
		*SpeedMul2 = *SpeedMul2*Dis;
		if (*SpeedMul2 > 1.0f)*SpeedMul2 = 1.0f;


		// 衝突した車の死亡している時判定している車のHpを０にする処理
		bool DeadFlg = false;

		//プレイヤーの死亡確認
		if ((player != nullptr) && (hitCar.Type == Hit_Type_Player))
		{
			if (player->Dead() == true)DeadFlg = true;
		}
		else {
			//敵の死亡確認
			if (hitCar.Type == Hit_Type_Enemy)
			{
				if ((enemy.size() > 0) && (hitCar.Numbar[0] < enemy.size()))
				{

					if (enemy[hitCar.Numbar[0]]->Dead() == true)DeadFlg = true;
				}
			}
		}
		if (DeadFlg == true)
		{
			// 敵の死亡させる
			if (judgCar.Type == Hit_Type_Enemy)
			{
				if ((enemy.size() > 0) && (judgCar.Numbar[0] < enemy.size()))
				{
					if (enemy[judgCar.Numbar[0]]->Dead() != true)
					{
						//HPをゼロにする
						int L_Hp = 0;
						enemy[judgCar.Numbar[0]]->SetNowHp(&L_Hp);
					}
				}
			}
		}

	}

	return true;
}

void GameScene::ForMoveEnd(D3DXMATRIX * Mat, const CONSTITUTION * Con, const QuaForMove * q, const D3DXMATRIX * TransMat)
{
	QuaForMove  L_q = *q;

	L_q.BodyHeight = 0;

	motion.Formove(&L_q, Con, groundManager->GetGround());

	*Mat = *TransMat * L_q.NowMat;
}

bool GameScene::GetBulletBirthFlg(void)
{
	if (GetEndFlg() == true)return false;
	if ((key.LClickF_N() == true) && (bulletBirthFlg == false))return false;
	return true;
}

bool GameScene::EnemyDelete(const unsigned int * EnemyNo)
{
	if ((*EnemyNo < 0) || (*EnemyNo > enemy.size() - 1))return false;

	if (enemy[*EnemyNo]->GetFlgCar() == false) {
		if (enemy[*EnemyNo]->GetDeadFlg() == false) {
			enemy[*EnemyNo]->SetDeadFlg(true);

			//死亡した敵がボスなら他の敵のHPをゼロにする
			if ((enemy[*EnemyNo]->Get_BossFlg() == true) && (enemy.size() > 0)) {
				int L_Hp = 0;
				for (auto && e : enemy)e->SetNowHp(&L_Hp);
			}

			// 爆発
			if(effectManager!=nullptr)effectManager->NewEffect(new c_Explosion3D(&enemy[*EnemyNo]->GetMatCar()));
			NewSound(&Co_Sound_Category_Explosion, 1, &judg.SetPosM(&enemy[*EnemyNo]->GetMatCar()), &Co_SoundNew);

			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

void GameScene::SetMenu(C_NextTouch * NewMenu)
{
	if (Menu != nullptr)delete Menu;

	Menu = NewMenu;
}

bool GameScene::UpdateMenu(void)
{
	if (Menu==nullptr)return false;

	int Touch = Menu->Touch();

	if (Touch > 0) {
		//mouse->SetTouchFlg();
	}
	else {
		return false;
	}

	if (fade.GetMoveFlg() != false)return false;

	if (key.LClickF() != true)return false;

	// タイトルを押しす処理
	if (Touch == co_TitleScene) {
		fade.SetNextScene(co_TitleScene, true);
		return true;
	}

	// セレクトを押す処理
	if (Touch == co_StageSelectScene) {
		fade.SetNextScene(co_StageSelectScene, true);
		return true;
	}

	// リトライを押しす処理
	if (Touch == co_GameScene) {
		bool DebugFlg = false;
		if (StageNo == Co_Stage_Type_Debug)DebugFlg = true;
		fade.SetNextStageNo(StageNo);
		fade.SetNextStageNo(&DebugFlg);
		fade.SetNextScene(co_GameScene, true);
		return true;
	}

	// プレイを押す処理
	if (Touch == co_PlayGame) {
		pause->SetDFlg(false);
		mouse->Init();
		mouse->ChaDrawFlg(false);
		pause->SetStaSavFlg(false);
		if (soundGameManager != nullptr) {
			soundGameManager->Restart();
		}

		//メニュー削除
		if (Menu != nullptr)delete Menu;
		Menu = new C_NextTouch();

		return true;
	}

	return true;
}

void GameScene::Pos2DUpdate(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
	if (damageNumDraw3DManager != nullptr)damageNumDraw3DManager->UpdatePos2D(mProj, mView, Viewport, &L_JudgMat);

	if (enemy.size() <= 0)return;
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//矢印計算
		enemy[e]->GetPos2DSet(mProj, mView, Viewport,&camera->GetPos());
	}
}

bool GameScene::UpdateGame(void)
{
	//ポーズ
	if (pause->GetDFlg() != false)return true;

	//ポーズ画面に移動の処理
	if (UpdateGamePause() != true)return true;

	if (JudgGameFrame() != true)return true;
	
	if (groundManager != nullptr)groundManager->Update(player);

	//車の情報の更新
	if (carPop != nullptr) {
		bool MoveFlg = GetCarPopUpdateMoveFlg();
		carPop->Update(&MoveFlg);
	}

	//========================================
	//プレイヤー
	//========================================

	//車の今の位置の更新
	if (player != nullptr) player->SetCarMoveMat();

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->SetCarMoveMat();
	}

	//カメラ-------------------------------------
	if (GetEndFlg() == false) {
		if (fade.GetMoveFlg() == false) {
			camera->UpdateM(true, mouse);
		}
		else {
			mouse->Init();
		}
	}
	//カメラ上限判定
	camera->RotXJudg(&player->GetMatCar());

	//プレイヤーと地面判定
	float Dis;
	unsigned int num;
	if (groundManager->JudgNowGround(&num, &Dis, nullptr, &player->GetMatCar()) == true) {
		player->SetGroNum(&num);//地面の取得
		eneFlg = true;//敵の出現開始
	}
	//敵
	UpdateEnemyAI();

	// 前進判定
	ForMoveJudg();

	//player======================================================================
	//playerの移動
	player->UpdateCarFM(groundManager->GetGround());

	float L_ResetSize = 1.0f;

	//移動ベクトルのサイズの初期化
	player->SetQuaVecSize(&L_ResetSize);
	//敵の移動
	if (enemy.size() > 0)
	{
		float L_ResetSize = 1.0f;
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Update(groundManager->GetGround());//Update
			//移動ベクトルのサイズの初期化
			enemy[i]->SetQuaVecSize(&L_ResetSize);
		}
	}

	// 横判定
	SideJudg();

	//最終Update
	//player->SetParts(camera->GetAngX(),camera->GetAngY());
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//if (enemy[e]->GetFlgCar() == true) {
				enemy[e]->SetParts(groundManager->GetGround());
			//}
		}
	}

	//カメラのクォータニオンのアップデート
	bool keyFlg = key.RClickF();
	if (GetEndFlg() != true)
	{
		keyFlg = key.RClickF();
	}
	camera->UpdateQua(&keyFlg, &player->GetMatCar());

	//カーブの車体の角度を反映
	player->SetCurRotMat();

	//カメラ行列の取得
	player->Set_CameraMat(&camera->GetMat());

	//playerのパーツ移動
	if (player->Update() != true) {
		SetGameOver();
	}

	//カメラのアップデート
	unsigned int i = 0;
	D3DXMATRIX Mat = player->Get_Camera_Mat();
	camera->Update(Mat);

	//カメラと壁判定
	int RadF = RadJudgF;
	camera->WallJudg(&RadF, groundManager);

	//プレイヤーと地面判定2
	if (groundManager->JudgNowGround(&num, &Dis, nullptr, &player->GetMatCar()) == true) {
		player->SetGroNum(&num);//地面の取得
		eneFlg = true;//敵の出現開始
	}

	//--------------------------------------------
	//車の動き完了後の処理
	//--------------------------------------------

	UpdateBullet();

	//================================================================================
	// 敵
	//================================================================================
	if (UpdateEnemy() == false) {
		if (GetEndFlg() == false) {
			GemeEndChange(&Co_Stage_End_Clear);
			SetMenu(new C_ClearTouch());
		}
	}

	// 空
	sky->Update(&player->GetMatCar());

	if (damageNumDraw3DManager != nullptr)damageNumDraw3DManager->Update();

	war->Update();

	if (effectManager != nullptr)effectManager->Update();

	UpdatePopEnd();

	return true;
}

bool GameScene::UpdateGamePause(void)
{
	//終わった時
	if (GetEndFlg() == true) {
		mouse->ChaDrawFlg(true);
	}
	else {
		//ポーズ
		if (key.RETURNKeyF() == true) {
			if (pause->GetDFlg() == false) {
				pause->SetDFlg(true);
				mouse->ChaDrawFlg(true);
				//ロードの許可
				if ((GetAsyncKeyState('8') & 0x8000) && (GetAsyncKeyState('9') & 0x8000) && (GetAsyncKeyState('0') & 0x8000)) {
					pause->SetStaSavFlg(true);
				}
				SetMenu(new C_PauseTouch());

				if (soundGameManager != nullptr) {
					soundGameManager->Stop();
				}

				return false;
			}
		}
	}

	return true;
}

bool GameScene::JudgGameFrame(void)
{
	//スロー再生
	if (CountNum >= MaxCount) {
		CountNum = 1;
		return true;
	}
	else {
		CountNum += 1;
	}
	return false;
}

bool GameScene::UpdatePlayerXTrans(void)
{
	//横判定
	//===========================================
	//車線変更
	//===========================================
	//左の車線に変更
	//カーブしたかどうかのFlg
	bool LRKeyFlg = false;

	if (GetEndFlg() != true) {

		if ((key.AKey() == true)) {
			D3DXMATRIX Trans;
			float X = -1.0f*0.08f;
			player->SetSideTransMat(&X);
			SideJudg(&Hit_Type_Player, nullptr, nullptr, &X);
			//カーブ
			player->SetRodAngY(-0.3f, true);
			LRKeyFlg = true;


		}
		//右の車線に変更
		if (key.DKey() == true) {
			D3DXMATRIX Trans;
			float X = 1.0f*0.08f;
			player->SetSideTransMat(&X);
			//横判定
			SideJudg(&Hit_Type_Player, nullptr, nullptr, &X);
			//カーブ
			player->SetRodAngY(0.3f, true);
			LRKeyFlg = true;
		}

	}
	if (LRKeyFlg == false)player->SetRodAngY(0.3f, false);

	return true;
}

bool GameScene::UpdatePopEnd(void)
{
	if (carPop == nullptr) return false;

	if (GetEndFlg() == true) return false;

	//現在の生存している敵数の調査
	int Num = 0;

	if (enemy.size() > 0) 
	{
		for (auto && e : enemy)
		{
			if (e->GetFlgCar() == true)Num++;
		}
	}

	carPop->Set_Now_Enemy_Num_N(&Num);

	//出現している車から車の出現の変更
	CarPopDataUpdate();

	// 道路の形状変更
	int RoadNo = carPop->Get_GroundNo();
	if (groundManager != nullptr)groundManager->SetGroundPop(&RoadNo);

	if (carPop->Get_Change_Class_EndFlg() == true) {
		if (carPop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Boss) {
			war->SetFlg(true);
			soundGameManager->BGMDelete();
			NewSound(&Co_Sound_Type_2D, &Co_Sound_Category_Warning, 1, &Co_SoundNew);
			war->New_Sound_Data_Change_No(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 4, &Co_SoundNew);
			return true;
		}
		if (carPop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Normal) {
			int No = 1;
			soundGameManager->BGMStart(&No);
			return true;
		}
	}
	
	//Popの終了確認処理
	if (carPop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_End) {

		//ゲームクリア状態にする
		SetGameClear();

		return false;
	}

	return true;
}

bool GameScene::GetCarPop(const int * Car_Type)
{
	//ゲーム終了Flg
	if (GetEndFlg() == true)return false;

	//プレイヤーが地面Noの取得Flg
	if (eneFlg != true)return false;

	//出現させる車の情報
	if (carPop == nullptr)return false;

	if (carPop->Get_Car_Pop_Flg_N() != true)return false;

	if (carPop->Get_Next_Car_Data_N().CarType != *Car_Type)return false;

	//出現可能
	return true;
}

bool GameScene::GetCarPopUpdateMoveFlg(void)
{
	if (GetEndFlg() == true)return false;

	if (war->GetFlg() == true)return false;

	return true;
}

void GameScene::SetGameOver(void)
{
	if (GetEndFlg() == true)return;

	//playerが死んだときの処理

	// 爆発
	effectManager->NewEffect(new c_Explosion3D(&player->GetMatCar()));
	NewSound(&Co_Sound_Category_Explosion, 1, &judg.SetPosM(&player->GetMatCar()), &Co_SoundNew);
	
	GemeEndChange(&Co_Stage_End_Over);

	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
	}
	player->SetSpeedCar(&(player->GetCon().Speed *0.0f));
	war->SetFlg(false);
	//メニューの表示
	SetMenu(new C_OverTouch());
}

void GameScene::SetGameClear(void)
{
	if (GetEndFlg() == true)return;

	GemeEndChange(&Co_Stage_End_Clear);
	SetMenu(new C_ClearTouch());

	int No = 5;
	soundGameManager->BGMStart(&No);
}

bool GameScene::UpdateBullet(void)
{
	//弾のMoveVecの加算
	if (player != nullptr) player->MoveVecBullet();

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->MoveVecBullet();
	}

	//弾の出現準備
	BulletInitPlayer();
	BulletInitEnemy();

	//弾の出現
	if (player != nullptr) 
	{
		if (GetEndFlg() != true) player->Shot();
	}

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->Shot();
	}

	//弾の当たり判定
	UpdateBulletJudg();

	//弾の更新
	if (player != nullptr) player->UpdateBullet();

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->UpdateBullet();
	}

	return true;
}

void GameScene::BulletInitPlayer(void)
{
	//照準のレイ判定
	S_RayHitJudgData HitData;
	HitData.Flg = false;

	BULLETJUDGDATA l_DisD;
	float Dis = 2000.0f;
	c_StructManager structManager;
	l_DisD = structManager.GetBULLETJUDGDATA(&structManager.GetCarType(&co_PlayerCar), &Dis);

	RAYDATA l_RayR;
	l_RayR.Mat = judg.SetMatP(&camera->GetPos());
	l_RayR.Ray = camera->GetVec();
	float Rad = 400.0f;

	//敵のレイ判定
	RayJudgEnemy(&l_DisD, &l_RayR, &Rad);
	if (l_DisD.HitType.Type > 0)HitData.Flg = true;

	//照準の変化
	if (HitData.Flg == true) {
		aiming->ChaFlg();
	}
	else {
		aiming->ResFlg();
	}

	//地面
	if (groundManager != nullptr)groundManager->BulletJudg(&l_DisD, &l_RayR, nullptr, &Rad);

	if (l_DisD.HitType.Type > 0)HitData.Flg = true;
	//建物のレイ判定
	//バレットの出現処理
	if (HitData.Flg == false) {
		player->Set_Gun_Ray_Data(&HitData);
	}
	else {

		//レイが当たった座標
		HitData.HitPos = judg.GetRayHitPos(&camera->GetPos(), &l_RayR.Ray, &l_DisD.SamllDis);

		player->Set_Gun_Ray_Data(&HitData);
	}

	bool T_Flg = false;
	if (key.LClickF_N() == true) {
		T_Flg = true;
	}
	unsigned int GunNo = 0;

	player->Set_Gun_Trigger(&GunNo, &T_Flg);

}

void GameScene::BulletInitEnemy(void)
{
	if (enemy.size() < 1)return;

	for (unsigned int ec = 0; ec < enemy.size(); ec++) 
	{
		if (enemy[ec]->Get_Gun_Num() <= 0) continue;

		for (unsigned int gc = 0; gc < enemy[ec]->Get_Gun_Num(); gc++) 
		{
			if (enemy[ec]->Get_Gun_Data(&gc).Ray_Judg_Flg != true) continue;

			//レイ判定
			c_StructManager structManager;
			BULLETJUDGDATA b;
			b.SamllDis = enemy[ec]->Get_Gun_Data(&gc).RayDis;
			b.JudgType = structManager.GetCarType(&co_EnemyCar, &ec);
			RAYDATA r;
			r.Mat = enemy[ec]->Get_Gun_Data(&gc).DrawBase.Mat;
			D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
			float Rad = (float)RadChara*2.0f;

			//レイ判定
			RayJudgPlayer(&b, &r, &Rad);
			RayJudgEnemy(&b, &r, &Rad);

			//レイが当たった時のFlg
			bool Ray_HitFlg = false;
			if (b.HitType.Type > 0)Ray_HitFlg = true;

			enemy[ec]->Set_Ray_Hit_Flg(&gc, &Ray_HitFlg);
			enemy[ec]->Set_Ray_Dis(&gc, &b.SamllDis);
		}
	}

}

bool GameScene::UpdateBulletJudg(void)
{
	BULLETJUDGDATA Bullet;

	RAYDATA BulletRay;

	float Rad = (float)RadJudgF;

	if (player != nullptr) 
	{
		if (player->GetBulletNum() > 0)
		{
			for (unsigned int bc = 0; bc < player->GetBulletNum(); bc++)
			{
				//初期化
				player->GetBulletMoveData(&Bullet, &BulletRay, &bc);

				//地面
				if (player->GetBulletGroWalJudgFlg(&bc) == true) 
				{
					bool GroWalJudgFlg;
					if (groundManager != nullptr)groundManager->BulletJudg(&Bullet, &BulletRay, &GroWalJudgFlg, &Rad);
					//次も壁と地面を判定できるかの代入
					player->SetBulletGroWalJudgFlg(&bc, &GroWalJudgFlg);
				}

				//敵
				RayJudgEnemy(&Bullet, &BulletRay, &Rad);
				//敵の球パーツ判定
				BulletJudgEnemyBall(&Bullet, &BulletRay, &Rad);
				//判定結果と弾の削除
				if (SetBulletDamage(&Bullet, &BulletRay, player->GetBulletDamage(&bc)) == true)player->DeleteBullet(&bc);
			}
		}
	}

	if (enemy.size() > 0)
	{
		for (unsigned int ec = 0; ec < enemy.size(); ec++) 
		{
			if (enemy[ec]->GetBulletNum() <= 0)continue;

			for (unsigned int bc = 0; bc < enemy[ec]->GetBulletNum(); bc++)
			{
				//初期化
				enemy[ec]->GetBulletMoveData(&Bullet, &BulletRay, &bc);

				//プレイヤー
				RayJudgPlayer(&Bullet, &BulletRay, &Rad);
				//地面
				if (enemy[ec]->GetBulletGroWalJudgFlg(&bc) == true)
				{
					bool GroWalJudgFlg;
					if (groundManager != nullptr)groundManager->BulletJudg(&Bullet, &BulletRay, &GroWalJudgFlg, &Rad);
					//次も壁と地面を判定できるかの代入
					enemy[ec]->SetBulletGroWalJudgFlg(&bc, &GroWalJudgFlg);
				}
				//敵
				RayJudgEnemy(&Bullet, &BulletRay, &Rad);
				//判定結果と弾の削除
				if (SetBulletDamage(&Bullet, &BulletRay, enemy[ec]->GetBulletDamage(&bc)) == true)enemy[ec]->DeleteBullet(&bc);
			}
		}
	}

	return true;
}

void GameScene::NewSound(const int * Type, const int * Category, const int No, const int * Change)
{
	if (soundGameManager == nullptr)return;

	C_Struct_Init C_S_Init;
	soundGameManager->New_Sound_Data(&C_S_Init.Get_S_SOUND_DATA(Type, Category, &No, Change));
}

void GameScene::NewSound(const int * Category, const int No, const D3DXVECTOR3 * Pos, const int * Change)
{
	if (soundGameManager == nullptr)return;

	soundGameManager->New_Sound_Data(Category, No, Pos, Change);
}

bool GameScene::GetEndFlg(void)
{
	if (gameEnd == nullptr)return true;

	return gameEnd->Get_EndFlg();
}

void GameScene::GemeEndChange(const int * Mode)
{
	if (gameEnd == nullptr)return;

	C_Game_End_Base* Game_End;

	Game_End=gameEnd->Change(Mode);

	if (Game_End != nullptr) {
		delete gameEnd;
		gameEnd = Game_End;
	}
}

void GameScene::PopEnemy(void)
{
	//エネミーの出現
	if (GetCarPop(&co_EnemyCar) != true) return;

	//車の情報取得
	S_CAR_INIT_DATA L_Data = carPop->Get_Next_Car_Data_N();

	//地面のナンバー
	unsigned int gNo;
	//地面の位置
	D3DXMATRIX GroundMat;
	//地面の初期位置の横幅
	float TransX;

	if (groundManager == nullptr)return;
	unsigned int playerGroundNo = player->GetCon().GroNum;
	groundManager->InitCarPopData(&gNo,&GroundMat,&TransX,&playerGroundNo,&L_Data);

	//出現できるかの判定
	if (CarPopJudg(&GroundMat, &TransX) != true)return;

	//ボスが出現する時の判定
	if (L_Data.CarNo > 100) {
		if (enemy.size() > 0) {
			for (auto && e : enemy) {
				if (e->GetCon().GroNum > gNo)return;
			}
		}
	}

	//敵の種類
	C_Enemy_Manager Manager;

	//出現
	enemy.push_back(Manager.Get_Enemy(&L_Data.CarNo, &GroundMat, &TransX));

	// 地面の当たり判定
	unsigned int num;
	float dis;
	if (groundManager->JudgNowGround(&num, &dis, nullptr, &enemy[(enemy.size() - 1)]->GetMatCar()) == true) {
		enemy[(enemy.size() - 1)]->SetGroNum(&num);
	}

	//出現後の処理
	carPop->Car_Init_Rear_N();
}

bool GameScene::CarPopJudg(const D3DXMATRIX * GroundMat, const float * TransX)
{
	D3DXMATRIX TmpMat;

	//地面の横幅の行列作成
	D3DXMatrixTranslation(&TmpMat, *TransX, 0.0f, 0.0f);

	//出現する初期位置の行列の合成
	TmpMat = TmpMat * (*GroundMat);

	//出現位置、走行中の車の位置
	D3DXVECTOR3 Pop_Pos, Car_Pos;

	//出現位置の初期化
	judg.SetPosM(&Pop_Pos, &TmpMat);

	//出現可能半径
	float Radius = 4.0f*2.0f;

	//プレイヤーとの判定
	if (player != nullptr)
	{
		if(player->BallJudgCar(&Pop_Pos,&Radius))return false;
	}

	//エネミーとの判定
	if (enemy.size() > 0)
	{
		for (auto && e : enemy)
		{
			if (e->BallJudgCar(&Pop_Pos, &Radius))return false;
		}
	}

	//出現可能
	return true;
}

void GameScene::RayJudgPlayer(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	if (player == nullptr)return;
	if (BJD->JudgType.Type == co_PlayerCar)return;

	player->RayJudg(BJD, nullptr, RD, Rad);
}

void GameScene::RayJudgEnemy(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad)
{
	if (enemy.size() <= 0)return;

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {

		if ((BJD->JudgType.Type==co_EnemyCar)&&(e == BJD->JudgType.Numbar[0]))continue;

		enemy[e]->RayJudg(BJD, &e, RD, Rad);

	}
}

void GameScene::BulletJudgEnemyBall(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, &RD->Mat);

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->BallJudgParst(BJD, &BPos, &co_EnemyCar, &e, &RD->Ray, Rad);
	}
}

bool GameScene::SetBulletDamage(const BULLETJUDGDATA * BJD, const RAYDATA * RD, const int Damage)
{
	if (BJD->HitType.Type < 0)return false;

	//地面///////////////////////////////////////////////////////////////////////////////////
	//地面
	if (BJD->HitType.Type == co_Ground) 
	{
		//火花
		D3DXVECTOR3 RayHitPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

		int SpeType = 0;
		float Ang = 0.0f;
		effectManager->NewEffect(new C_BulGro(&groundManager->GetGroundMat(&BJD->HitType.Numbar[0]), &RayHitPos));

		//弾痕３D
		float Ray_Dis = BJD->SamllDis - 0.01f;

		RayHitPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

		if (effectManager != nullptr)effectManager->NewEffect(new C_BulletHole3D(&groundManager->GetGroundMat(&BJD->HitType.Numbar[0]), &RayHitPos, 2));

		//被弾音の初期化
		if (soundGameManager != nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Ground, &RayHitPos);

		return true;
	}

	//壁
	if (BJD->HitType.Type == co_Wall)
	{
		//火花
		D3DXVECTOR3  RayHitPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

		int SpeType = 1;
		float Ang = 0.0f;
		//火花
		unsigned int i = (int)BJD->HitType.Numbar[1];
		for (int s = 0; s < 5; s++) {
			effectManager->NewEffect(new C_SparkDamage(&groundManager->GetWallMat(&BJD->HitType.Numbar[0], &i), &RayHitPos, &SpeType, &Ang));
		}
		//弾痕３D
		float Ray_Dis = BJD->SamllDis - 0.01f;

		RayHitPos=judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

		effectManager->NewEffect(new C_BulletHole3D(&groundManager->GetWallMat(&BJD->HitType.Numbar[0], &i), &RayHitPos, 1));

		//被弾音の初期化
		if (soundGameManager != nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Wall, &RayHitPos);

		return true;
	}

	//プレイヤー/////////////////////////////////////////////////////////////////////////////
	//車体
	if (BJD->HitType.Type == co_PlayerCar)
	{
		if (player->SetHP(Damage, false) == true) {
			//ダメージを受けた時
			int sc = -10;
			score->ScoreUp(&sc);

			//被弾座標
			D3DXVECTOR3 RayPos;

			//被弾音の初期化
			if (soundGameManager != nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Player, &RayPos);
		}
		return true;
	}
	//標準パーツ
	if (BJD->HitType.Type == co_PlayerParts)return true;
	//銃
	//if ()return true;

	//エネミー//////////////////////////////////////////////////////////////////////////////
	//車体
	if (BJD->HitType.Type == co_EnemyCar)
	{
		if (enemy[BJD->HitType.Numbar[0]]->GetFlgCar() == false)return true;

		bool DamageFlg = enemy[BJD->HitType.Numbar[0]]->SetHP(Damage, false);

		if (damageNumDraw3DManager != nullptr)
		{
			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
			damageNumDraw3DManager->NewDamageNumDraw(&BJD->JudgType.Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, &Damage, &DamageFlg, &L_JudgMat);
		}

		//被弾音の初期化
		// 被弾座標
		D3DXVECTOR3 RayPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);
		if (soundGameManager == nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Enemy, &RayPos, &DamageFlg);

		return true;
	}
	//標準パーツ
	if (BJD->HitType.Type == co_EnemyParts)
	{
		bool DamageFlg = enemy[BJD->HitType.Numbar[0]]->Damage_CarParts(&BJD->HitType.Numbar[1], &Damage);

		if (damageNumDraw3DManager != nullptr)
		{
			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
			damageNumDraw3DManager->NewDamageNumDraw(&BJD->JudgType.Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, &Damage, &DamageFlg, &L_JudgMat);
		}

		//被弾音の初期化
		// 被弾座標
		D3DXVECTOR3 RayPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);
		if (soundGameManager == nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Enemy, &RayPos, &DamageFlg);

		return true;
	}
	//銃
	if (BJD->HitType.Type == co_EnemyGun)
	{
		bool DamageFlg = enemy[BJD->HitType.Numbar[0]]->Damage_Gun(&BJD->HitType.Numbar[1], &Damage);

		if (damageNumDraw3DManager != nullptr)
		{
			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
			damageNumDraw3DManager->NewDamageNumDraw(&BJD->JudgType.Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, &Damage, &DamageFlg, &L_JudgMat);
		}

		//被弾音の初期化
		// 被弾座標
		D3DXVECTOR3 RayPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);
		if (soundGameManager == nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Enemy, &RayPos, &DamageFlg);

		return true;
	}

	//当たっていない
	return false;
}

void GameScene::EnemyStop(const unsigned int * e, const int * Side_Judg_Car_Type)
{
	if (*Side_Judg_Car_Type != Hit_Type_Player)return;

	if (enemy[*e]->GetFlgCar() != true)return;

	if (enemy[*e]->Get_Move_Stop_Time() > 0)return;

	int Time = 60 * 8, L_Speed = player->GetCon().NowSpeed;

	enemy[*e]->Set_Move_Stop_Time(&Time,&L_Speed);
}

void GameScene::FrustumCulling(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	S_Frustum_Vec FV_Data;

	judg.Get_Frustum_NormalVec(&FV_Data, mProj, mView, Viewport, &camera->GetPos());

	if (groundManager != nullptr)groundManager->FrustumCulling(&FV_Data);
}

void GameScene::BallJudgPlayer(bool * JudgFlg, float * SmallDis, s_CarType * HitCar
	, const s_CarType * JudgCar, const D3DXMATRIX * EndMat, const float * Radius
	, const bool * CollisionJudg_TrueFlg)
{
	//プレイヤーとプレイヤーで判定しないようにする
	if (JudgCar->Type == Hit_Type_Player)return;

	//全ての戦闘が終了しているときプレイヤーと判定しない
	if (GetEndFlg() != false) return;

	//判定できない状態の場合判定をしない
	if (*CollisionJudg_TrueFlg != true)return;

	// 距離判定
	if (player->BallJudgCar(JudgFlg, SmallDis, EndMat, Radius) != true) return;

	*JudgFlg = true;
	HitCar->Type = Hit_Type_Player;
}

void GameScene::BallJudgEnemy(bool * JudgFlg, float * SmallDis, s_CarType * HitCar
	, const s_CarType * JudgCar, const D3DXMATRIX * EndMat, const float * Radius
	, const bool * CollisionJudg_TrueFlg)
{
	//出現している敵がいない場合レイ判定しない
	if (enemy.size() <= 0)return;

	//全ての戦闘が終了した場合プレイヤーの車と判定しない
	if ((GetEndFlg() == true) && (JudgCar->Type == Hit_Type_Player))return;

	for (unsigned int e = 0; e < enemy.size(); e++) {

		//同じ敵で判定しない
		if ((JudgCar->Type == Hit_Type_Enemy) && (JudgCar->Numbar[0] == e))continue;

		//敵が空を飛んでいる場合判定しない
		if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

		//判定する敵が判定できない状態でプレイヤーと判定する場合判定しない
		//if ((*Car_Type == Hit_Type_Player) && (enemy[e]->Get_CollisionJudg_TrueFlg() != true))continue;

		// 距離判定
		if (enemy[e]->BallJudgCar(JudgFlg, SmallDis, EndMat, Radius) != true) continue;

		*JudgFlg = true;
		HitCar->Type = Hit_Type_Enemy;
		HitCar->Numbar[0] = e;

		/*if (*Car_Type == Hit_Type_Player) {
			bool Flg = false;
			enemy[e]->Set_CollisionJudg_TrueFlg(&Flg);
		}*/
	}
}

void GameScene::CapsuleJudgPlayer(float * SmallDis, int * hitNum, s_CarType * HitCar, const S_Capsule * c, const s_CarType * JudgCar, const bool * CollisionJudgTrueFlg, const bool * ForMoveJudgFlg)
{
	//プレイヤーとプレイヤーで判定しないようにする
	if (JudgCar->Type == Hit_Type_Player)return;

	//全ての戦闘が終了しているときプレイヤーと判定しない
	if (GetEndFlg() != false) return;

	//判定できない状態の場合判定をしない
	if (*CollisionJudgTrueFlg != true)return;

	// 距離判定
	if (player->capsuleJudg(SmallDis, hitNum, c, ForMoveJudgFlg) != true) return;

	c_StructManager structManager;
	*HitCar = structManager.GetCarType(&Hit_Type_Player);
}

void GameScene::CapsuleJudgEnemy(float * SmallDis, int * hitNum, s_CarType * HitCar, const S_Capsule * c, const s_CarType * JudgCar, const bool * CollisionJudgTrueFlg, const bool * ForMoveJudgFlg)
{
	//出現している敵がいない場合レイ判定しない
	if (enemy.size() <= 0)return;

	//全ての戦闘が終了した場合プレイヤーの車と判定しない
	if ((GetEndFlg() == true) && (JudgCar->Type == Hit_Type_Player))return;

	for (unsigned int e = 0; e < enemy.size(); e++) 
	{

		//同じ敵で判定しない
		if ((JudgCar->Type == Hit_Type_Enemy) && (JudgCar->Numbar[0] == e))continue;

		//敵が空を飛んでいる場合判定しない
		if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

		//判定する敵が判定できない状態でプレイヤーと判定する場合判定しない
		//if ((*Car_Type == Hit_Type_Player) && (enemy[e]->Get_CollisionJudg_TrueFlg() != true))continue;

		// 距離判定
		if (enemy[e]->capsuleJudg(SmallDis, hitNum, c,ForMoveJudgFlg) != true) continue;

		c_StructManager structManager;
		*HitCar = structManager.GetCarType(&Hit_Type_Enemy, &e);

		/*if (*Car_Type == Hit_Type_Player) {
			bool Flg = false;
			enemy[e]->Set_CollisionJudg_TrueFlg(&Flg);
		}*/
	}
}

void GameScene::CarPopDataUpdate(void)
{
	/*出現している敵の情報作成*/

	////出現している敵の数
	//int L_Enemy_Num = (int)enemy.size();

	////動的配列の初期化用配列数
	//int L_Init_Num = L_Enemy_Num;

	//if (L_Init_Num <= 0)L_Init_Num = 1;

	////敵の情報
	//S_ENEMY_DATA *L_Enemy_Data = new S_ENEMY_DATA[L_Init_Num];

	////出現している敵の作成
	//if ((L_Enemy_Num > 0) && (L_Enemy_Data != nullptr)) {

	//	if (enemy.size() > 0) {

	//		for (unsigned int e = enemy.size() - 1; e >= 0; e--)
	//		{
	//			//情報の作成
	//			L_Enemy_Data[(int)e].CarFlg = enemy[e]->GetFlgCar();
	//			L_Enemy_Data[(int)e].BossFlg = enemy[e]->Get_BossFlg();
	//			L_Enemy_Data[(int)e].Phase_Now = enemy[e]->Get_Gun_Update_Data().NowPhase;
	//		}

	//	}
	//}

	//出現している車の情報で車の情報の更新
	if (carPop != nullptr)carPop->M_Car_Pop_Update_N(enemy);

	////メモリの解放
	//if (L_Enemy_Data != nullptr)delete[] L_Enemy_Data;
}
