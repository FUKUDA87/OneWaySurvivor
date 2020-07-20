#include "EmptyBullet.h"
#include"../../../../MaterialManager/XfileManager.h"
#include"../../../../GameSource/Judgment.h"

extern XFileManager xfileManager;

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void DrawMesh(XFILE *XFile);

c_EmptyBullet::c_EmptyBullet(const D3DXMATRIX * GunMat)
{
	mat = *GunMat;

	//ロード
	mesh = xfileManager.GetMesh("Bullet1-3.x");

	int Big = 40, Small = -20;
	Big = Big - Small;
	moveVec = D3DXVECTOR3(0.07f, 0.065f + (float)(rand() % Big + Small) / 1000.0f, 0.0f);

	yDown = -0.01f;

	scalSize = 0.22f;

	int c = 30;
	count = new C_Count(&c);
}

c_EmptyBullet::~c_EmptyBullet()
{
	if (count != nullptr)delete count;
}

bool c_EmptyBullet::Update(const s_CarEffectUpdateData * updateData)
{
	Judg judg;
	judg.VecMatIn(&mat, &updateData->MoveVec);

	moveVec.y += yDown;

	D3DXMATRIX TmpMat;

	judg.setTransMat(&TmpMat, &moveVec);

	mat = TmpMat * mat;

	return count->Update_Count();
}

void c_EmptyBullet::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	D3DXMATRIX tmp;
	D3DXMatrixScaling(&tmp, scalSize, scalSize, scalSize);
	tmp = tmp * mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &tmp);
	DrawMesh(&mesh);
}
