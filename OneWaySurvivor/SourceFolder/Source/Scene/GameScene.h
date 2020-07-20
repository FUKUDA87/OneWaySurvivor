#pragma once
#include<d3dx9.h>
#include<vector>
#include"SceneBase.h"
#include"../Ground/Sky.h"
#include"../Player/Aiming.h"
#include"../Player/Camera.h"
#include"../GameSource/Debug.h"
#include"../GameSource/Text_Num.h"
#include"../Draw/2D/GameEnd/Game_End_Now.h"
#include"../GameSource/Struct.h"
#include"../Draw/2D/Warning.h"
#include"../Draw/2D/Pause.h"
#include"../GameSource/Judgment.h"
#include"../Draw/3D/Spear.h"
#include"../GameSource/Motion.h"
#include"../Draw/2D/Score.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../Player/PlayerA.h"
#include"../Enemy/EnemyA.h"
#include"../Player/PlayerBody.h"
#include"../Draw/Menu/PauseTouch.h"
#include"../Draw/Menu/OverTouch.h"
#include"../Enemy/EnemySelect.h"
#include"../Enemy/Data/Base&Manager/EnemySpeedManager.h"
#include"../Const/Const_Draw_Judg.h"
#include"../StageData/CarPop/Car_Pop_New.h"
#include"../Ground/StageGround/Ground_Pop_New.h"
#include"../Sound/GameSoundManager.h"
#include"../Draw/DamageNum/Damage_Move_A.h"
#include"../Draw/DamageNum/Damage_Move_B.h"
#include"../Ground/Ground_Object.h"
#include"../GameSource/Option/Option.h"
#include"../Draw/Menu/ClearTouch.h"
#include"../Ground/GroundManager.h"
#include"../Draw/Effect/EffectManager.h"
#include"../Draw/2D/Screen/Screen.h"
#include"../Draw/DamageNum/DamageNumDraw3DManager.h"
#include"../GameSource/StructClass/SideSparkData.h"

extern Motion motion;

//#ifndef GameScene_H
//#define GameScene_H

#define RadChara 200//キャラクターの範囲

class GameScene :public SceneBase
{
public:
	GameScene(const int stageNum);
	GameScene(const int stageNum,const bool *DebugFlg);
	~GameScene();

	// 3D描画
	void Render3D(void);

	// 3D描画の上からの視点
	void Render3DScreen(void);

	// 2D描画
	void Render2D(void);

	// カメラ
	void SetCamera(void);

	// 更新処理
	bool Update(void);

private:

	//判定用の関数のクラス
	Judg judg;

	//デバッグ用----------------
	int CountNum, MaxCount;//スロー再生用
	Spear *spear;
	D3DXMATRIX SpeMat;
	//--------------------------
	//プレイヤーの情報
	C_PlayerBody *playerBody;
	//プレイヤー
	C_PlayerBase *player;//

	std::vector<C_EnemyAi*>enemy;
	bool eneFlg;//出現の切り替え
	Sky *sky;
	Aiming *aiming;
	Camera *camera;
	Debug *debug;
	//文字表示
	C_Text_Num *textDraw;

	c_GroundManager *groundManager;

	C_Game_End_Base *gameEnd;

	Warning *war;

	int StageNo;


	Pause *pause;

	//スコア
	C_Score *score;

	//バレットバースFlg
	bool bulletBirthFlg;

	//マウス
	C_Mouse *mouse;
	//キー
	C_KeyTrue key;

	//弾痕３D
	C_EffectManager *effectManager;

	//タッチ
	C_NextTouch* Menu;

	/*車の沸き情報*/
	C_Car_Pop_New *carPop;

	//音の管理
	c_GameSoundManager* soundGameManager;

	c_DamageNumDraw3DManager *damageNumDraw3DManager;

	c_Screen *screen;  // ミニ画面

	// 火花出現位置の情報
	C_SideSparkData *sideSparkData;

	// 初期化
	void Init(void);

	bool UpdateEnemy(void);

	//壁と車体横の判定
	void SideJudg();
	void SideJudg(const int * CarType, const unsigned int * No1, const unsigned int * No2, const float *MoveVecX);
	void SideJudg(bool *WallJudgFlg, const s_CarType *carType, const float *MoveVecX, const int *FirstCarType);

	//敵の誕生と思考
	bool UpdateEnemyAI(void);

	//前進レイ判定
	bool ForMoveJudg(void);
	bool ForMoveJudg(const int *CarType, const unsigned int *CarNo
		, const D3DXVECTOR3 *MoveVec, float *SpeedMul2, const bool *CollisionJudgTrueFlg);

	//移動後の行列作成
	void ForMoveEnd(D3DXMATRIX *Mat,const CONSTITUTION *Con,const QuaForMove *q,const D3DXMATRIX *TransMat);
	
	//BulletBirthFlg
	bool GetBulletBirthFlg(void);

	//デリートエネミー
	bool EnemyDelete(const unsigned int *EnemyNo);

	//メニューの入れ
	void SetMenu(C_NextTouch* NewMenu);

	//メニューの処理
	bool UpdateMenu(void);
	
	//Pos2D計算
	void Pos2DUpdate(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//ゲーム本編の更新
	bool UpdateGame(void);

	//ゲーム本編時のポーズ画面移動関数
	bool UpdateGamePause(void);

	//ゲームのフレーム数の判定
	bool JudgGameFrame(void);

	//今いる車で横判定
	/*bool UpdateCarSideJudg(void);*/

	//プレイヤーの横移動処理
	bool UpdatePlayerXTrans(void);

	//ゲーム本編の最後の更新
	bool UpdatePopEnd(void);

	//車の出現確認
	bool GetCarPop(const int *CarType);

	//車の出現の更新の停止命令渡し
	bool GetCarPopUpdateMoveFlg(void);

	//ゲームオーバー時
	void SetGameOver(void);

	//ゲームクリア時
	void SetGameClear(void);

	//全ての弾の更新
	bool UpdateBullet(void);

	//弾の出現準備の更新
	void BulletInitPlayer(void);
	void BulletInitEnemy(void);

	//弾の判定の更新
	bool UpdateBulletJudg(void);

	void NewSound(const int *Type, const int *Category, const int No, const int *Change);
	void NewSound(const int *Category, const int No,const D3DXVECTOR3* Pos, const int *Change);

	//ゲーム終了Flg
	bool GetEndFlg(void);

	//ゲームのモードチェンジ
	void GemeEndChange(const int *Mode);

	//敵の出現
	void PopEnemy(void);

	//車の出現可能調査(出現可能ならtrue)
	bool CarPopJudg(const D3DXMATRIX *GroundMat, const float *TransX);

	//車の生存確認

	/*弾*/

	//弾判定集
	void RayJudgPlayer(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	void RayJudgEnemy(BULLETJUDGDATA* BJD,const RAYDATA *RD, const float *Rad);
	void BulletJudgEnemyBall(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	//弾判定によるダメージ計算
	bool SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD,const int Damage);

	/*レイ判定*/
	
	//衝突による敵のAiと攻撃をStopさせる
	void EnemyStop(const unsigned int *e,const int *SideJudgCarType);

	//視錐台カリング
	void FrustumCulling(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	// プレイヤーと球判定
	void BallJudgPlayer(bool *JudgFlg, float *SmallDis,s_CarType * HitCar,const s_CarType * JudgCar,
		const D3DXMATRIX *Mat,const float *Radius,const bool *CollisionJudgTrueFlg);

	// 敵と球判定
	void BallJudgEnemy(bool *JudgFlg, float *SmallDis, s_CarType * HitCar, const s_CarType * JudgCar,
		const D3DXMATRIX *Mat, const float *Radius, const bool *CollisionJudgTrueFlg);

	// プレイヤーとカプセル判定
	void CapsuleJudgPlayer(float *SmallDis, int *hitNum, s_CarType * HitCar,const S_Capsule *c, const s_CarType * JudgCar,const bool *CollisionJudgTrueFlg, const bool *ForMoveJudgFlg);

	// 敵とカプセル判定
	void CapsuleJudgEnemy(float *SmallDis, int *hitNum, s_CarType * HitCar, const S_Capsule *c, const s_CarType * JudgCar, const bool *CollisionJudgTrueFlg, const bool *ForMoveJudgFlg);

	//出現している車の情報の作成と車の出現の更新
	void CarPopDataUpdate(void);


};

//#endif // !GameScene_H
