#include "WallSideHitSpark.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;

C_WallSideHitSpark::C_WallSideHitSpark(const D3DXMATRIX * InitMat, const bool * InitFlg, const bool *LeftFlg)
{
	Mat = *InitMat;

	Tex = textureManager.GetTexture("spark10-1.png", 300, 300, NULL);

	//ƒ|ƒŠƒSƒ“•\¦—p‚ÌMat‚Ì‰Šú‰»
	PolNum = rand() % 1 + 2;
	PolMat = new D3DXMATRIX[PolNum];

	if (*InitFlg == true)
	{
		zDown = 0.0f;
		yUp = 0.0f;
		yDown = 0.0f;
		PolSize = 0.04f;

		//X‰ñ“]‚ÆˆÚ“®s—ñ
		D3DXMATRIX RotY, Trans;
		float AngY;
		AngY = (float)(rand() % 10)* 0.8f;
		if (*LeftFlg == true) AngY *= -1.0f;

		D3DXMatrixRotationY(&RotY, D3DXToRadian(AngY));
		float TransY = (float)(rand() % 50 - 25) / 100.0f;
		D3DXMatrixTranslation(&Trans, 0.0f, TransY, 0.5f);
		Mat = RotY * Trans * Mat;
		for (int p = 0; p < PolNum; p++) PolMat[p] = Mat;

		//X²‚Ì‰ñ“]Šp“x‚ğ‹‚ß‚é
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
		//ˆÚ“®ˆ—‚Ì‰Šú‰»
		zDown = -(float)(rand() % 11 + 20) / 30.0f;

		//X²‚Ì‰ñ“]Šp“x‚ğ‹‚ß‚é
		int Big = 35, Small = -5;
		Big = Big - Small;
		int Ang = rand() % Big + Small;
		yUp = (float)Ang / 100.0f;
		yDown = -0.025f;
		//‘¶İŠÔ‚ÌŒvZ
		int Time = Ang;
		if (Time < 0)Time *= -1;
		count->setNowCount(Time);
		PolSize = 0.03f;
		//X‰ñ“]‚ÆˆÚ“®s—ñ
		D3DXMATRIX RotY, Trans;
		//‰ñ“]‚Æ‚¸‚ç‚µ
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
			//ãˆÚ“®‚ÆŒã‚ëˆÚ“®
			D3DXMATRIX Tmp;
			D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
			Mat = Tmp * Mat;

			Mat._42 += yUp;

			//ƒWƒƒƒ“ƒvˆ—
			UpdateMoveY();

			//s—ñ‚ÌXV
			for (int i = PolNum - 1; i > 0; i--)PolMat[i] = PolMat[i - 1];
			PolMat[0] = Mat;
		}

	}
}
