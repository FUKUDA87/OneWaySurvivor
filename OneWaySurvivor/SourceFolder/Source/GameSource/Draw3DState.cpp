#include "Draw3DState.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
void DrawMesh(XFILE *XFile);

StateDraw3D * C_Draw3DStateA::Action(Object3D *Object)
{
	if (Object->Base.DrawFlg == true) {
		lpD3DDevice->SetTransform(D3DTS_WORLD, &Object->Base.Mat);
		DrawMesh(&Object->Mesh);
	}
	return nullptr;
}
