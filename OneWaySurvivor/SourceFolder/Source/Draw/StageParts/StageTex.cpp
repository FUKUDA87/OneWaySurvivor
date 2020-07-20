#include "StageTex.h"

StageTex::StageTex(const int No, const D3DXVECTOR2 WindPos)
{
	//ステージTexロード
	mod.TEX = { NULL,250,50 };
	mod.TEX.Tex = textureManager.GetTexture("CharStage2.png", mod.TEX.Width, mod.TEX.Height, NULL);
	mod.Base.Pos = D3DXVECTOR2(0.0f, 0.0f);
	mod.Base.ScaPos = D3DXVECTOR2(1.0f, 1.0f);
	wind.Base.ScaPos = D3DXVECTOR2(150.0f / wind.TEX.Width, 150.0f / wind.TEX.Height);
	wind.Base.Pos = WindPos;//D3DXVECTOR3((float)SCRW / 5.0f*1.0f, (float)SCRH/4.0f, 0.0f);
	D3DXMatrixTranslation(&mod.Base.Trans, 0.0f, -((float)wind.TEX.Height / 2.0f*wind.Base.ScaPos.y / 2.0f)*0.9f, 0.0f);
	sizeM = D3DXVECTOR2(0.8f, 0.5f*0.7f);
	//ナンバー
	StageNo = No;
	Num.Base.Pos = D3DXVECTOR2(0.0f, 0.0f);
	Num.Base.ScaPos = D3DXVECTOR2(1.0f, 1.0f);
	D3DXMatrixTranslation(&Num.Base.Trans, 0.0f, ((float)wind.TEX.Height / 2.0f*wind.Base.ScaPos.y / 2.0f), 0.0f);
}

void StageTex::Draw2DN()
{
	int w = Num.TEX.Width / 10, h = Num.TEX.Height;
	RECT rcNum[] = {
	{0 + w * 0,0,w + w * 0,h},
	{0 + w * 1,0,w + w * 1,h},
	{0 + w * 2,0,w + w * 2,h},
	{0 + w * 3,0,w + w * 3 - 3,h},
	{0 + w * 4,0,w + w * 4,h},
	{0 + w * 5,0,w + w * 5,h},
	{0 + w * 6,0,w + w * 6,h},
	{0 + w * 7,0,w + w * 7,h},
	{0 + w * 8,0,w + w * 8,h},
	{0 + w * 9,0,w + w * 9,h} };
	char cScore[64];
	sprintf_s(cScore, sizeof(cScore), "%d", StageNo);
	Num.Base.ScaPos = D3DXVECTOR2((float)wind.TEX.Width*wind.Base.ScaPos.x / ((float)(25 * 2)), (float)wind.TEX.Height*wind.Base.ScaPos.y / ((float)(25 * 2)));
	Num.Base.ScaPos *= 0.3f;
	D3DXMatrixScaling(&Num.Base.Scal, Num.Base.ScaPos.x, Num.Base.ScaPos.y, NULL);
	D3DXMATRIX spWorld, spTrans;
	int i;
	for (i = 0; cScore[i] != '\0'; i++);
	for (i -= 1; i >= 0; i--) {
		Num.Base.Mat = wind.Base.Mat;
		D3DXMATRIX tmp;
		tmp = Num.Base.Scal*Num.Base.Trans* Num.Base.Mat;
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Num.TEX.Tex, &rcNum[cScore[i] - '0'], &D3DXVECTOR3((float)25, (float)25, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void StageTex::DrawSu()
{
	Draw2D();
	Draw2DM();
	Draw2DN();
}
