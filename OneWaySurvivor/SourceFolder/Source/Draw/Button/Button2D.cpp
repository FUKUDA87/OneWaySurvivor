#include "Button2D.h"
#include"../../GameSource/Judgment.h"

extern LPD3DXSPRITE lpSprite;	// スプライト

void C_Button2D::Draw2D(void)
{
	D3DXMATRIX tmp, ScalMat,RotZMat;
	D3DXMatrixTranslation(&tmp, pos.x, pos.y, NULL);
	D3DXMatrixScaling(&ScalMat, scalSize.x, scalSize.y, NULL);
	D3DXMatrixRotationZ(&RotZMat, D3DXToRadian(angZ));
	tmp = RotZMat * tmp;
	tmp = ScalMat * tmp;

	RECT rcH = { 0,0, width, height };
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(Tex, &rcH, &D3DXVECTOR3((float)width / 2.0f, (float)height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

bool C_Button2D::Update(const D3DXVECTOR2 * Pos)
{
	pos = *Pos; 
	return true;
}

bool C_Button2D::TouchJudg(void)
{
	Judg judg;
	return judg.PlaneCri(&pos, &scalSize, &width, &height);
}

void C_Button2D::setScalSize(const float *s, const int letterNum)
{
	scalSize = D3DXVECTOR2((*s) * (float)letterNum / (float)width, (*s) / (float)height);
}
