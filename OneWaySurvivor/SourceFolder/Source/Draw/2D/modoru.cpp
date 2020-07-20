#include "modoru.h"

Modoru::Modoru()
{
	//戻るtexのロード
	mod.TEX = { NULL,256,256 };
	mod.TEX.Tex = textureManager.GetTexture("back4.png", mod.TEX.Width, mod.TEX.Height, NULL);
	//戻るの座標の初期化
	mod.Base.Pos = D3DXVECTOR2(0.0f, 0.0f);
	//戻るのScal座標の初期化
	mod.Base.ScaPos = D3DXVECTOR2(1.0f, 1.0f);
	D3DXMatrixTranslation(&mod.Base.Trans, 0.0f, 0.0f, 0.0f);
	wind.Base.ScaPos *= 0.1f*0.8f;
	wind.Base.Pos = D3DXVECTOR2((float)SCRW / 17.0f, (float)SCRH / 13.0f);
	sizeM = D3DXVECTOR2(0.7f, 0.7f);
}

void Modoru::Draw2DM()
{
	mod.Base.ScaPos = D3DXVECTOR2(wind.TEX.Width*wind.Base.ScaPos.x / mod.TEX.Width, wind.TEX.Height*wind.Base.ScaPos.y / mod.TEX.Height);
	mod.Base.ScaPos.x *= sizeM.x;
	mod.Base.ScaPos.y *= sizeM.y;
	RECT rcM = { 0,0, mod.TEX.Width, mod.TEX.Height };
	D3DXMatrixScaling(&mod.Base.Scal, mod.Base.ScaPos.x, mod.Base.ScaPos.y, NULL);
	D3DXMATRIX tmp;
	mod.Base.Mat = wind.Base.Mat;
	tmp = mod.Base.Scal*mod.Base.Trans *mod.Base.Mat;
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(mod.TEX.Tex, &rcM, &D3DXVECTOR3((float)mod.TEX.Width / 2.0f, (float)mod.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
}

bool Modoru::UpdateM()
{
	if (judg.PlaneCri(&judg.SetPos2DM(&wind.Base.Mat), &wind.Base.ScaPos, &wind.TEX.Width, &wind.TEX.Height) == true) {
		return false;
	}
	return true;
}

void Modoru::DrawSu()
{
	Draw2D();
	Draw2DM();
}

bool Modoru::UpdateSu()
{
	Update();
	if (UpdateM() == false) {
		return false;
	}
	return true;
}
