#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Score {
public:
	C_Score();
	~C_Score();
	//初期化
	void Init(void);
	//アップデート
	bool Update(void);
	//表示
	void Draw2D(void);
	//スコアのインクリメント
	void ScoreUp(const int *UpNum);

protected:

private:
	//スコア文字画像・スコア数画像・スコアのポイント
	CHARA2D score, snum,sPoint;
	//スコア量
	int ScoreNum,ScoreNumNow;
	//スコアの上がり下がり値
	int ScoreNumUD;
	//下がりのアニメーション
	float Anime, AnimeFrame;
	D3DXMATRIX StartMat, EndMat;
	int DrawCount;
	int alphaP;
};