#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"FadeMove.h"
#include"FadeOut.h"
#include"FadeIn.h"
#include"FadeDraw.h"
#include"../Scene/SceneBase.h"
#include"../Scene/SceneNo.h"

class C_Fade 
{
public:
	
	// 初期化
	void Init();

	~C_Fade();

	// 更新処理
	bool Update();

	// 描画処理
	void Draw();

	// フェードアウトさせる処理
	void StartFadeout(void);

	// フェードインをさせる処理
	void StartFadein(void);

	//動きのフラグ渡し
	bool GetMoveFlg(void) {
		return MoveFlg;
	}
	//Move完了Flg渡し
	bool GetMoveEndFlg(void) {
		return MoveEndFlg;
	}

	// 次のシーンの渡し
	SceneBase* GetNextScene(void);

	// 次のシーンの情報のセット
	void SetNextScene(const int SceneNo,const bool BlackFlg);
	void SetNextStageNo(const int StageNo);
	void SetNextStageNo(const bool *GameSceneDebugFlg);
private:
	C_FadeMove *FadeMove;


	C_FadeDraw *fadeDraw;

	int alpha;
	
	//フェードのFlg;
	bool MoveFlg, MoveEndFlg;

	//フェード色
	int FadeColor;

	int NextSceneNo;
	int NextStageNo;
	bool gameSceneDebugFlg;

	//色変え
	void SetColor(bool BlackFlg);
};