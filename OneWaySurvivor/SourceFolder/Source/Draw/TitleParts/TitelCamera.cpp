#include "TitelCamera.h"

bool TitleCamera::Update(D3DXMATRIX mat)
{
	//LookÇÃê›íË
	D3DXVECTOR3 Pos;
	Pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	camLook = Pos + D3DXVECTOR3(0.0f, 0.7f, 0.0f);
	camSize = 3.5f;

	//PosÇÃê›íË
	camAngY = -0.0f;
	camAngX = 7.0f;
	D3DXMATRIX RotXMat, RotYMat, WorldMat;
	D3DXMatrixRotationX(&RotXMat, D3DXToRadian(camAngX));
	D3DXMatrixRotationY(&RotYMat, D3DXToRadian(camAngY));
	RotYMat = RotXMat * RotYMat*mat;
	D3DXVec3TransformNormal(&camPos, &D3DXVECTOR3(0.0f, 0.0f, camSize), &RotYMat);
	camPos += camLook;

	return true;
}
