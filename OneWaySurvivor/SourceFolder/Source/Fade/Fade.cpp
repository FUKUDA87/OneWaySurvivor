#include "Fade.h"
#include"../Scene/TitleScene.h"
#include"../Scene/StageSelectScene.h"
#include"../Scene/GameScene.h"

void C_Fade::Init()
{
	fadeDraw = new C_FadeDraw();

	SetColor(true);

	FadeMove = new C_FadeNoMove();
	MoveFlg = false;
	MoveEndFlg = false;
	alpha = 0;

	NextSceneNo = 0;
	NextStageNo = 0;

	gameSceneDebugFlg = false;
}

C_Fade::~C_Fade()
{
	if (FadeMove != nullptr) delete FadeMove;

	if (fadeDraw != nullptr)delete fadeDraw;
}

bool C_Fade::Update()
{
	C_FadeMove *Move;
	Move = FadeMove->Action(&MoveFlg, &MoveEndFlg, &alpha, 6);
	if (Move != nullptr) {
		delete FadeMove;
		FadeMove = Move;
	}
	return MoveFlg;
}

void C_Fade::Draw()
{
	if (fadeDraw != nullptr)fadeDraw->Draw(&alpha, &FadeColor);
}

void C_Fade::StartFadeout(void)
{
	if (MoveFlg != false)return;

	if (MoveEndFlg != false)return;

	MoveFlg = true;
}

void C_Fade::StartFadein(void)
{
	if (MoveEndFlg == false)return;

	MoveEndFlg = false;

	MoveFlg = true;
}

SceneBase * C_Fade::GetNextScene(void)
{
	switch (NextSceneNo)
	{
	case co_TitleScene:
		return new TitleScene();
	case co_StageSelectScene:
		return new StageSelectScene();
	case co_GameScene:
		return new GameScene(NextStageNo,&gameSceneDebugFlg);
	}
	return nullptr;
}

void C_Fade::SetNextScene(const int SceneNo, const bool BlackFlg)
{
	NextSceneNo = SceneNo;

	SetColor(BlackFlg);

	StartFadeout();
}

void C_Fade::SetNextStageNo(const int StageNo)
{
	NextStageNo = StageNo;
}

void C_Fade::SetNextStageNo(const bool * GameSceneDebugFlg)
{
	gameSceneDebugFlg = *GameSceneDebugFlg;
}

void C_Fade::SetColor(bool BlackFlg)
{
	static bool blackFlg = true;
	blackFlg = BlackFlg;
	if (blackFlg == true) {
		FadeColor = 0;
	}
	else {
		FadeColor = 255;
	}
}
