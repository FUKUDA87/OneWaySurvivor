#include "DrawBase.h"

C_DrawBase::C_DrawBase()
{
	M_S_DrawBase = Init_S_DrawBase();
}

S_DrawBase C_DrawBase::Init_S_DrawBase(void)
{
	S_DrawBase db;
	D3DXMatrixTranslation(&db.Mat, 0.0f, 0.0f, 0.0f);
	db.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	db.TransPos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	db.ScalPos= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	db.AngX = 0.0f;
	db.AngY = 0.0f;
	db.AngZ = 0.0f;
	return S_DrawBase();
}
