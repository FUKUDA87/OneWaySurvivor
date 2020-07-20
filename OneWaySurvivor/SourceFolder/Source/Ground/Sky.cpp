#include"Sky.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern TextureManager textureManager;
extern XFileManager xfileManager;

void DrawMesh(XFILE *XFile);

void Sky::Init()
{
	sky.Mesh=xfileManager.GetMesh("Sky_1_1.x");
	D3DXMatrixTranslation(&sky.Base.Trans, 0, 0, 0);//位置
	D3DXVECTOR3 Pos(500.0f, 210.0f, 500.0f);
	D3DXMatrixScaling(&sky.Base.Scal, Pos.x, Pos.y, Pos.z);
	D3DXMatrixRotationY(&sky.Base.RotY, D3DXToRadian(180));//回転
}

Sky::Sky(){
	Init();
}

bool Sky::Update(const D3DXMATRIX *PM) {
	D3DXMatrixTranslation(&sky.Base.Trans, PM->_41, PM->_42, PM->_43);//位置
	sky.Base.Mat = sky.Base.RotY *sky.Base.Trans;
	return true;
}
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
void Sky::Draw(void) {
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DXMATRIX TmpMat;
	TmpMat = sky.Base.Scal * sky.Base.Mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	DrawMesh(&sky.Mesh);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}