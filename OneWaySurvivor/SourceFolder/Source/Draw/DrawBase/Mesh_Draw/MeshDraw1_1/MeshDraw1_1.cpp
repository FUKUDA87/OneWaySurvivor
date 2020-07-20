#include "MeshDraw1_1.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス


void DrawMesh(XFILE *XFile);


void C_MeshDraw_1_1::Draw(const D3DXMATRIX * Mat)
{
	if (M_Mesh.lpMesh == nullptr)return;

	lpD3DDevice->SetTransform(D3DTS_WORLD, Mat);
	DrawMesh(&M_Mesh);
}
