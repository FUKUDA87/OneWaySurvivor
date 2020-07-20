#include "Num2DBase.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト


//void C_Num2DBase::SetNum(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Scal)
//{
//	Num.Base.Pos = *Pos;
//	Num.Base.ScaPos = *Scal;
//}
//
//void C_Num2DBase::SetTex(std::string FileName, const int * Width, const int * Height)
//{
//	//画像情報のセット
//	Num.TEX.Width = *Width;
//	Num.TEX.Height = *Height;
//	//画像のロード
//	Num.TEX.Tex = textureManager.GetTexture(&FileName[0], Num.TEX.Width, Num.TEX.Height, NULL);
//}

//void C_Num2DBase::Draw2DNB(const int * TmpNum)
//{
//	if (Num.TEX.Tex == nullptr)return;
//
//	//表示
//
//}

//D3DXMATRIX C_Num2DBase::GetDrawMatNDB(const D3DXMATRIX * Mat)
//{
//	D3DXMATRIX Tmp;
//	//行列の準備
//	judg.ScalingMat(&Num.Base.Scal, &Num.Base.ScaPos);
//	//行列の合成
//	Tmp = Num.Base.Scal**Mat;
//
//	return Tmp;
//}

c_Num2DBase::c_Num2DBase(int TexNo)
{
	// 画像のロード
	NumTex.Width = 500;
	NumTex.Height = 50;
	NumTex.Tex = textureManager.GetTexture("CharNum2.png", NumTex.Width, NumTex.Height, NULL);
}

void c_Num2DBase::Draw(const int * Num, const D3DXVECTOR2 * Pos
	, const D3DXVECTOR2 * TransVec, const D3DXVECTOR2 * ScalPos
	, const bool * RevFlg)
{
	int w = NumTex.Width / 10, h = NumTex.Height;
	RECT rcNum[] = {
	{0 + w * 0,0,w + w * 0,h},
	{0 + w * 1,0,w + w * 1,h},
	{0 + w * 2,0,w + w * 2,h},
	{0 + w * 3,0,w + w * 3 - 3,h},
	{0 + w * 4,0,w + w * 4,h},
	{0 + w * 5,0,w + w * 5,h},
	{0 + w * 6,0,w + w * 6,h},
	{0 + w * 7 + 2,0,w + w * 7,h},
	{0 + w * 8,0,w + w * 8 + 2,h},
	{0 + w * 9 + 2,0,w + w * 9,h} };

	char cNum[64];
	sprintf_s(cNum, sizeof(cNum), "%d", *Num);
	int i;
	for (i = 0; cNum[i] != '\0'; i++);

	// 数字の初期位置の調整
	D3DXVECTOR2 vec;
	vec.x = (float)w*ScalPos->x*TransVec->x;
	vec.y = (float)h*ScalPos->y*TransVec->y;

	D3DXMATRIX tmpMat, TransMat, ScalMat, DrawMat;
	D3DXMatrixTranslation(&tmpMat, Pos->x + vec.x, Pos->y + vec.y, NULL);
	D3DXMatrixScaling(&ScalMat, ScalPos->x / (float)w, ScalPos->y / (float)h, NULL);

	Judg judg;
	D3DXMatrixTranslation(&TransMat, (float)w*ScalPos->x*judg.Reverse(RevFlg), 0.0f, NULL);

	if (*RevFlg == false)
	{
		for (i -= 1; i >= 0; i--)
		{
			tmpMat *= TransMat;
			DrawMat = ScalMat * tmpMat;
			lpSprite->SetTransform(&DrawMat);
			lpSprite->Draw(NumTex.Tex, &rcNum[cNum[i] - '0'], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	else {
		for (int n = 0; n < i; n++)
		{
			if (n != 0)tmpMat *= TransMat;
			DrawMat = ScalMat * tmpMat;
			lpSprite->SetTransform(&DrawMat);
			lpSprite->Draw(NumTex.Tex, &rcNum[cNum[n] - '0'], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void c_Num2DBase::Draw(const int * Num, const D3DXVECTOR2 * Pos
	, const float * ScalSize, const bool * RevFlg)
{
	int w = NumTex.Width / 10, h = NumTex.Height;
	RECT rcNum[] = {
	{0 + w * 0,0,w + w * 0,h},
	{0 + w * 1,0,w + w * 1,h},
	{0 + w * 2,0,w + w * 2,h},
	{0 + w * 3,0,w + w * 3 - 3,h},
	{0 + w * 4,0,w + w * 4,h},
	{0 + w * 5,0,w + w * 5,h},
	{0 + w * 6,0,w + w * 6,h},
	{0 + w * 7 + 2,0,w + w * 7,h},
	{0 + w * 8,0,w + w * 8 + 2,h},
	{0 + w * 9 + 2,0,w + w * 9,h} };

	char cNum[64];
	sprintf_s(cNum, sizeof(cNum), "%d", *Num);
	int i;
	for (i = 0; cNum[i] != '\0'; i++);

	// 数字の初期位置の調整
	D3DXVECTOR2 scalPos;
	scalPos = D3DXVECTOR2((float)w, (float)h);
	D3DXVec2Normalize(&scalPos, &scalPos);
	scalPos *= (*ScalSize);

	D3DXMATRIX tmpMat, TransMat, ScalMat, DrawMat;
	D3DXMatrixTranslation(&tmpMat, Pos->x, Pos->y, NULL);
	D3DXMatrixScaling(&ScalMat, scalPos.x / (float)w, scalPos.y / (float)h, NULL);

	Judg judg;
	D3DXMatrixTranslation(&TransMat, scalPos.x*judg.Reverse(RevFlg), 0.0f, NULL);

	if (*RevFlg != false)
	{
		for (i -= 1; i >= 0; i--)
		{
			tmpMat = TransMat * tmpMat;
			DrawMat = ScalMat * tmpMat;
			lpSprite->SetTransform(&DrawMat);
			lpSprite->Draw(NumTex.Tex, &rcNum[cNum[i] - '0'], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	else {
		for (int n = 0; n < i; n++)
		{
			if (n != 0)tmpMat = TransMat * tmpMat;
			DrawMat = ScalMat * tmpMat;
			lpSprite->SetTransform(&DrawMat);
			lpSprite->Draw(NumTex.Tex, &rcNum[cNum[n] - '0'], &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void c_Num2DBase::Draw(const int * Num, const D3DXVECTOR2 * Pos, const D3DXVECTOR2 * ScalSize)
{
	int w = NumTex.Width / 10, h = NumTex.Height;
	RECT rcNum[] = {
	{0 + w * 0,0,w + w * 0,h},
	{0 + w * 1,0,w + w * 1,h},
	{0 + w * 2,0,w + w * 2,h},
	{0 + w * 3,0,w + w * 3 - 3,h},
	{0 + w * 4,0,w + w * 4,h},
	{0 + w * 5,0,w + w * 5,h},
	{0 + w * 6,0,w + w * 6,h},
	{0 + w * 7 + 2,0,w + w * 7,h},
	{0 + w * 8,0,w + w * 8 + 2,h},
	{0 + w * 9 + 2,0,w + w * 9,h} };

	char cNum[64];
	sprintf_s(cNum, sizeof(cNum), "%d", *Num);
	int i;
	for (i = 0; cNum[i] != '\0'; i++);

	D3DXMATRIX Mat, scalMat, tmp,TransMat;
	D3DXVECTOR2 pos = *Pos;
	D3DXMatrixScaling(&scalMat, ScalSize->x, ScalSize->y, NULL);

	if (i > 1)
	{
		D3DXVECTOR2 TransVec = D3DXVECTOR2((float)w*ScalSize->x, 0.0f)*-1.0f;

		int Num = i / 2;

		// 偶数の確認
		if ((i % 2) < 1)
		{
			pos += (TransVec / 2.0f);
			Num--;
		}

		for (int m = 0; m < Num; m++)
		{
			pos += TransVec;
		}

		TransVec *= -1.0f;
		D3DXMatrixTranslation(&TransMat, TransVec.x, TransVec.y, NULL);
	}

	D3DXMatrixTranslation(&Mat, pos.x, pos.y, NULL);

	for (int n = 0; n < i; n++)
	{
		if (n > 0)Mat = TransMat * Mat;

		tmp = scalMat * Mat;
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(NumTex.Tex, &rcNum[cNum[n] - '0'], &D3DXVECTOR3((float)w / 2.0f, (float)h / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}
