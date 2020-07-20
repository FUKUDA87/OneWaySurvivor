#include "Object_Base.h"
#include"../../MaterialManager/XFileManager.h"
#include"../../GameSource/Judgment.h"

extern XFileManager xfileManager;

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void DrawMesh(XFILE *XFile);


C_Object_Base::C_Object_Base()
{
	M_Set_Mat_No = 0;
	M_Base.Base.ScaPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	M_Base.Base.DrawFlg = false;
}

void C_Object_Base::Draw(void)
{
	if ((M_Mesh.Mesh.lpMesh == nullptr) || (M_Base.Base.DrawFlg != true))return;

	lpD3DDevice->SetTransform(D3DTS_WORLD, &M_Base.Base.DrawMat);
	DrawMesh(&M_Mesh.Mesh);
}

void C_Object_Base::Update_DrawMat(const D3DXMATRIX * Mat)
{
	M_Base.Base.DrawMat = *Mat;
}

void C_Object_Base::Mesh_Load(std::string FileName)
{
	M_Mesh = xfileManager.GetMeshB(FileName);

	M_Base.Base.DrawFlg = true;

	Init();

	Judg judg;

	judg.Get_Draw_Radius(&M_Base.CullingRad, &M_Mesh.Data.BigVec, &M_Mesh.Data.SmallVec, &M_Base.Base.ScaPos);
}

void C_Object_Base::Init(void)
{
	
}

