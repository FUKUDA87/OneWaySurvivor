#include "CarSideHitSpark.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;

C_CarSideHitSpark::C_CarSideHitSpark(const D3DXMATRIX * InitMat, const bool * InitFlg)
{
	//画像のロード
	int SparkType;
	if ((rand() % 15) != 1) 
	{
		SparkType = 3;
		PolSize = 0.015f;
	}
	else {
		SparkType = 6;
		//ポリゴンサイズの初期化
		PolSize = 0.01f;
	}
	char TexName[100];
	sprintf_s(TexName, sizeof(TexName), "Spark1-9-%d.png", SparkType);
	Tex = textureManager.GetTexture(TexName, 300, 300, NULL);

	//ポリゴンの初期化
	PolNum = 3;
	PolMat = new D3DXMATRIX[PolNum];

	//移動処理の初期化
	yDown = -0.005f;
	zDown = -(float)(rand() % (20 - 5) + 5) / 10.0f;

	//角度の初期化
	Mat = *InitMat;
	//X軸の回転角度を求める
	int Big = 6000, Small = -6000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small) / 100.0f;
	yUp = Ang / 100.0f*0.5f;
	yDown = yUp / 10.0f;
	if (yDown > 0.0f)yDown *= -1.0f;
	//存在時間の計算
	if (Ang < -3000.0f)count->setNowCount(3);
	if (Ang > -3000.0f)count->setNowCount(6);
	if (Ang > 0.0f)count->setNowCount(20);
	if (Ang > 3000.0f)count->setNowCount(30);
	if (*InitFlg == true)count->setNowCount(1);
	//X回転と移動行列
	D3DXMATRIX Rot, Trans;
	//回転とずらし
	float AngY;// , zMove;
	AngY = (float)(rand() % 50) / 10.0f;
	if ((rand() % 2) == 1)AngY *= -1.0f;
	//zMove = 0.15f;
	D3DXMatrixRotationY(&Rot, D3DXToRadian(AngY));
	//ずらす
	//D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, zMove);
	//位置の初期化
	Mat = Rot /** Trans*/ * Mat;
	//他の行列を初期化
	for (int p = 0; p < PolNum; p++) PolMat[p] = Mat;
	
	for (int i = 0; i < PolNum; i++) {
		//上移動と後ろ移動
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
		Mat = Tmp * Mat;
		Mat._42 += yUp;
		//ジャンプ処理
		yUp += yDown;
		//行列の更新
		for (int i = (PolNum - 1); i > 0; i--) PolMat[i] = PolMat[i - 1];
		PolMat[0] = Mat;
	}
}
