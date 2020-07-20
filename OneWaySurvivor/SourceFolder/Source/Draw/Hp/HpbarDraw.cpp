#include "HpbarDraw.h"

C_HpbarDraw::~C_HpbarDraw()
{
	Delete();
}

void C_HpbarDraw::Init(C_HpbarBase * InitHpBase)
{
	Delete();

	HpbarBase = InitHpBase;
}

void C_HpbarDraw::Delete(void)
{
	if (HpbarBase == nullptr)return;
		
	delete HpbarBase;
	
}

void C_HpbarDraw::Draw2D(const CHARABASE * CharaBase)
{
	if (HpbarBase == nullptr)return;

	HpbarBase->Draw2D(&CharaBase->NowHp, &CharaBase->MaxHp);
}

void C_HpbarDraw::Draw3D(const CHARABASE * CharaBase, const D3DXMATRIX * Mat, const D3DXVECTOR3 * CamPos, const D3DXVECTOR3 *ScalPos)
{
	if (HpbarBase == nullptr)return;

	HpbarBase->Draw3D(&CharaBase->NowHp, &CharaBase->MaxHp, Mat, CamPos,ScalPos);
}
