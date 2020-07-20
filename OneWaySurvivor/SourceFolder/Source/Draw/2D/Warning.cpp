#include "Warning.h"
#include"../../GameSource/Judgment.h"

Warning::Warning()
{
	//Waning文字
	//ロード
	war.TEX = { NULL,510,109 };
	war.TEX.Tex = textureManager.GetTexture("CharEmergency1.png", war.TEX.Width, war.TEX.Height, NULL);
	//拡大
	war.Base.ScaPos = D3DXVECTOR2(9.0f*50.0f / (float)war.TEX.Width, 50.0f / (float)war.TEX.Height);
	war.Base.ScaPos *= 2.9f;
	war.Base.ScaPos.y *= 1.5f;
	Judg judg;
	judg.setScalingMat(&war.Base.Scal, &war.Base.ScaPos);
	//赤黒
	//ロード
	yel.TEX = { NULL,1300,100 };
	yel.TEX.Tex = textureManager.GetTexture("warnB3.png", yel.TEX.Width, yel.TEX.Height, NULL);
	//拡大
	D3DXMatrixScaling(&yel.Base.Scal, 1280.0f / (float)yel.TEX.Width, 1.0f*0.8f, 1.0f);

	//点滅の初期化
	warFlg = false;
	count = 0;
	countEnd = 5;
	MaxAlphaW = 255;
	SmallAlphaW = 50;
	alphaW = SmallAlphaW;
	if (alphaW <= SmallAlphaW) {
		k = -1;
	}
	else {
		k = 1;
	}
	alphaY = 0;
}

bool Warning::Update(void)
{
	if (warFlg == true) {
		alphaW -= 4 * k;
		alphaY += 3;
		if (alphaY > 150) {
			alphaY = 150;
		}
		if (alphaW < SmallAlphaW) {
			alphaW = SmallAlphaW;
			k = -1;
		}
		if (alphaW > MaxAlphaW) {
			alphaW = MaxAlphaW;
			count += 1;
			k = 1;
		}
		//終了確認
		if (count >= countEnd) {
			//終了処理
			warFlg = false;
			Change_Menu_All();
			New_Sound_Data(&Co_Sound_Type_2D, &Co_Sound_Category_Warning, 1, &Co_SoundDelete);
		}
	}
	return true;
}

void Warning::Draw2D(void)
{
	if (warFlg == true) {
		D3DXMATRIX tmpMat;
		RECT rcWa = { 0,0,war.TEX.Width, war.TEX.Height };
		D3DXMatrixTranslation(&war.Base.Mat, 1280.0f / 2.0f, 720.0f / 2.0f, NULL);
		tmpMat = war.Base.Scal*war.Base.Mat;
		lpSprite->SetTransform(&tmpMat);
		lpSprite->Draw(war.TEX.Tex, &rcWa, &D3DXVECTOR3((float)war.TEX.Width / 2.0f, (float)war.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(alphaW, 255, 255, 255));//

		tmpMat = war.Base.Mat;
		int x = 1;
		RECT rcYe = { 0,0,yel.TEX.Width, yel.TEX.Height };
		for (int i = 0; i < 2; i++) {
			x *= -1;
			D3DXMatrixTranslation(&yel.Base.Trans, 0.0f, 720.0f / 3.0f*x, NULL);
			yel.Base.Mat = yel.Base.Trans*tmpMat;
			yel.Base.Mat = yel.Base.Scal*yel.Base.Mat;
			lpSprite->SetTransform(&yel.Base.Mat);
			lpSprite->Draw(yel.TEX.Tex, &rcYe, &D3DXVECTOR3((float)yel.TEX.Width / 2.0f, (float)yel.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(alphaY, 255, 255, 255));//
		}
	}
}
