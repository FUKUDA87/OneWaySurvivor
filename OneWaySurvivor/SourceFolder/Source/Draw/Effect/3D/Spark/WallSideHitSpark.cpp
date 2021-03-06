#include "WallSideHitSpark.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;

C_WallSideHitSpark::C_WallSideHitSpark(const D3DXMATRIX * InitMat, const bool * InitFlg, const bool *LeftFlg)
{
	Mat = *InitMat;

	Tex = textureManager.GetTexture("spark10-1.png", 300, 300, NULL);

	//ポリゴン表示用のMatの初期化
	PolNum = rand() % 1 + 2;
	PolMat = new D3DXMATRIX[PolNum];

	if (*InitFlg == true)
	{
		zDown = 0.0f;
		yUp = 0.0f;
		yDown = 0.0f;
		PolSize = 0.04f;

		//X回転と移動行列
		D3DXMATRIX RotY, Trans;
		float AngY;
		AngY = (float)(rand() % 10)* 0.8f;
		if (*LeftFlg == true) AngY *= -1.0f;

		D3DXMatrixRotationY(&RotY, D3DXToRadian(AngY));
		float TransY = (float)(rand() % 50 - 25) / 100.0f;
		D3DXMatrixTranslation(&Trans, 0.0f, TransY, 0.5f);
		Mat = RotY * Trans * Mat;
		for (int p = 0; p < PolNum; p++) PolMat[p] = Mat;

		//X軸の回転角度を求める
		int Big = 200, Small = -200;
		Big = Big - Small;
		float AngX = (float)(rand() % Big + Small) / 10.0f;
		D3DXMATRIX RotX;
		D3DXMatrixRotationX(&RotX, D3DXToRadian(AngX));
		Mat = RotX * Mat;
		for (int p = 0; p < PolNum; p++) PolMat[p] = Mat;

		D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, -4.0f);

		for (int p = 0; p < PolNum - 1; p++)
		{
			Mat = Trans * Mat;
			for (int i = (PolNum - 1); i > 0; i--) PolMat[i] = PolMat[i - 1];
			PolMat[0] = Mat;
		}
	}
	else {
		//移動処理の初期化
		zDown = -(float)(rand() % 11 + 20) / 30.0f;

		//X軸の回転角度を求める
		int Big = 35, Small = -5;
		Big = Big - Small;
		int Ang = rand() % Big + Small;
		yUp = (float)Ang / 100.0f;
		yDown = -0.025f;
		//存在時間の計算
		int Time = Ang;
		if (Time < 0)Time *= -1;
		count->setNowCount(Time);
		PolSize = 0.03f;
		//X回転と移動行列
		D3DXMATRIX RotY, Trans;
		//回転とずらし
		float AngY, zMove;
		AngY = (float)(rand() % 10);
		zMove = 0.0f;

		if (*LeftFlg == true) AngY *= -1.0f;

		D3DXMatrixRotationY(&RotY, D3DXToRadian(AngY));

		D3DXMatrixTranslation(&Trans, 0.0f, (float)(rand() % 100) / 1000.0f*-1.0f, zMove);

		Mat = RotY *Trans * Mat;
		for (int p = 0; p < PolNum; p++) PolMat[p] = Mat;

		for (int i = 0; i < PolNum+2; i++)
		{
			//上移動と後ろ移動
			D3DXMATRIX Tmp;
			D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
			Mat = Tmp * Mat;

			Mat._42 += yUp;

			//ジャンプ処理
			UpdateMoveY();

			//行列の更新
			for (int i = PolNum - 1; i > 0; i--)PolMat[i] = PolMat[i - 1];
			PolMat[0] = Mat;
		}

	}
}
