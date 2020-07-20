#include "StageCamera.h"
#include"../../GameSource/Judgment.h"

void StageCam::Init_Car(void)
{
	CamAngX = 0.0f;
	CamAngY = 0.0f;
	CamSize = 3.0f;
	//変更して調整
	CamSizeCha = 0.01f;
	TransCha = 0.01f;
	sen = 4.0f;

	Height = 0.0f;

}

StageCam::StageCam()
{
	camAngY = -90.0f;
	camAngX = -10.0f;
	sizeZ = 3.5f;
	upY = 0.4f;

	Init_Car();

}

bool StageCam::Update(D3DXMATRIX mat, D3DXMATRIX tmp, bool MouFlg)
{

	D3DXMATRIX cMat;
	cMat = tmp * mat;
	Judg judg;
	judg.SetPosM(&camLook, &cMat);
	D3DXMATRIX RotMat;
	if (MouFlg == true) {
		camAngY += upY;
	}
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(camAngY), D3DXToRadian(camAngX), 0.0f);
	D3DXVec3TransformCoord(&camPos, &D3DXVECTOR3(0.0f, 0.0f, sizeZ), &RotMat);
	camPos += camLook;
	return true;
}

bool StageCam::UpdateCar(C_Mouse *Mouse)
{

	Mouse->CamUpdate(&CamAngX, &CamAngY, sen, 1, 1, true);
	float OverX = 85.0f;
	if (CamAngX < -OverX)CamAngX = -OverX;
	if (CamAngX > OverX)CamAngX = OverX;
	//ズームイン
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		CamSize -= CamSizeCha;
		if (CamSize <= 1.6f)CamSize = 1.6f;
	}
	//ズームアウト
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		CamSize += CamSizeCha;
	}
	//行列のセット
	D3DXMATRIX RotX, RotY, World;
	D3DXMatrixRotationX(&RotX, D3DXToRadian(CamAngX));
	D3DXMatrixRotationY(&RotY, D3DXToRadian(CamAngY));
	//行列の合成
	World = RotX * RotY;
	//World = World * Body.Base.Mat;
	//位置のセット
	D3DXVec3TransformNormal(&camPos, &D3DXVECTOR3(0.0f, 0.0f, CamSize), &World);
	camLook=D3DXVECTOR3(0.0f, Height, 0.0f);
	camPos += camLook;

	return false;
}
