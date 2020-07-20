#include "OkButton.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_OK::C_OK(const D3DXVECTOR2 * CharScal, const D3DXVECTOR2 * WindPos, const D3DXVECTOR2 * WindScal)
{
	//初期化
	InitOK();

	wind.Base.Pos = *WindPos;
	wind.Base.ScaPos.x *= WindScal->x;
	wind.Base.ScaPos.y *= WindScal->y;

	//文字の拡大
	OK.Base.ScaPos.x *= CharScal->x;
	OK.Base.ScaPos.y *= CharScal->y;

	OK.Base.Pos = wind.Base.Pos;
	
}

void C_OK::Draw2DOK(void)
{
	if (OK.Base.DrawFlg != true)return;

	Draw2D();

	//文字表示------------------------------------------------------------------------------------
	//位置のセット
	D3DXMatrixScaling(&OK.Base.Scal, OK.Base.ScaPos.x, OK.Base.ScaPos.y,NULL);
	D3DXMATRIX tmp;
	tmp = OK.Base.Scal*wind.Base.Mat;

	//表示
	//if (OK.Base.DrawFlg == false) {
		RECT rcH = { 0,0, OK.TEX.Width, OK.TEX.Height };
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(OK.TEX.Tex, &rcH, &D3DXVECTOR3((float)OK.TEX.Width / 2.0f, (float)OK.TEX.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	//}
	//else {
	//	RECT rcH = { 0,0, Stage.TEX2.Width, Stage.TEX2.Height };
	//	lpSprite->SetTransform(&tmp);
	//	lpSprite->Draw(Stage.TEX2.Tex, &rcH, &D3DXVECTOR3((float)Stage.TEX2.Width / 2.0f, (float)Stage.TEX2.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	//}
}

bool C_OK::Touch(void)
{
	if (OK.Base.DrawFlg != true)return false;
	//タッチ確認
	if (judg.PlaneCri(&wind.Base.Pos, &wind.Base.ScaPos, &wind.TEX.Width, &wind.TEX.Height) == true)return true;

	return false;
}

void C_OK::InitOK(void)
{
	//画像のロード
	OK.TEX = { NULL,163,81 };
	OK.TEX.Tex = textureManager.GetTexture("CharOk1.png", OK.TEX.Width, OK.TEX.Height, NULL);

	//文字の初期化
	int CharNum = 2;
	OK.Base.ScaPos = D3DXVECTOR2(50.0f*(float)CharNum / (float)OK.TEX.Width, 50.0f / (float)OK.TEX.Height);

	OK.Base.DrawFlg = false;
}
