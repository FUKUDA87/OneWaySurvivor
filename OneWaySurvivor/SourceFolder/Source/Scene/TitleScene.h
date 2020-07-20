#pragma once
#include<d3dx9.h>
#include"SceneBase.h"
#include"../Draw/TitleParts/TitleTex.h"
#include"../Draw/TitleParts/StartTex.h"
#include"../Draw/TitleParts/TitelCamera.h"
#include"../Ground/Sky.h"
#include"../Ground/Wall.h"
#include"../Draw/2D/BulletHole.h"
#include"../Key/CMouse.h"
#include"../Key/Key.h"
#include"../Player/PlayerBody.h"
#include"../Player/PlayerA.h"
#include"../Sound/GameSoundManager.h"
#include"../Ground/Ground_Object.h"
#include"../GameSource/Option/Option.h"
#include"../Ground/GroundManager.h"

template<class T>
inline void SafeRelease(T& lpAdd)
{
	if (lpAdd != nullptr) {
		lpAdd->Release();
		lpAdd = nullptr;
	}
}
class TitleScene :public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Render2D(void);   // 2D描画
	void Render3D(void);   // 3D描画
	bool Update(void);     // 更新処理
	void SetCamera(void);  // カメラ

private:

	Judg judg;  // 判定用の関数のクラス

	c_GroundManager *groundManager;

	LPDIRECT3DTEXTURE9 Tex;
	TitleTex *titleTex;
	StartTex *startTex;
	
	//プレイヤー
	C_PlayerBase *player;
	//プレイヤーの情報
	C_PlayerBody *PlaBodData;

	TitleCamera *camera;
	Sky *sky;
	//弾痕
	std::vector<C_BulletHole*>BulHol;

	//マウス
	C_Mouse *mouse;
	//キー
	Key key;

	//ゲームの終了
	bool Game_End(void);

	c_GameSoundManager* M_C_Sound_Manager;

	//ステージ選択シーンへの移動
	void Next_StageScene_Switch(void);
};
