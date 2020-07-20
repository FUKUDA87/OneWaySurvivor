#include"XFileManager.h"
#include"../GameSource/Judgment.h"

void LoadMesh(struct XFILE *XFile, const char FName[]);
void ReleaseMesh(struct XFILE *XFile);
extern LPDIRECT3DDEVICE9 lpD3DDevice;

XFileManager::~XFileManager() {
	AllDelete();
}
XFILE XFileManager::GetMesh(std::string FileName)
{
	XFILE *Mesh;
	if (xfileList.find(FileName) == xfileList.end()) {
		Mesh = new XFILE;
		char FileName2[100];
		sprintf_s(FileName2, sizeof(FileName2), "../GameFolder/Material/XFile/%s", &FileName[0]);
		LoadMesh(Mesh, FileName2);
		LPD3DXMESH TmpMesh;
		Mesh->lpMesh->CloneMeshFVF(D3DXMESH_NPATCHES | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, lpD3DDevice, &TmpMesh);
		Mesh->lpMesh->Release();
		Mesh->lpMesh = TmpMesh;
		xfileList[FileName] = Mesh;
	}
	else {
		Mesh = xfileList[FileName];
	}
	return *Mesh;
}
XFILE_B XFileManager::GetMeshB(std::string FileName)
{
	XFILE_B Xfile;

	Xfile.Mesh = GetMesh(FileName);

	S_MeshData *Data;

	if (MeshDataList.find(FileName) == MeshDataList.end()) {

		Data = new S_MeshData();

		Data->NumVertex = Xfile.Mesh.lpMesh->GetNumVertices();

		CLONEVERTEX *pV;
		D3DXVECTOR3 BigPos, SmallPos;
		Xfile.Mesh.lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

		BigPos = SmallPos = pV->Pos;

		Judg judg;
		for (DWORD No = 1; No < Data->NumVertex; No++) 
		{
			judg.Big(&BigPos, &(pV + No)->Pos);
			judg.Small(&SmallPos, &(pV + No)->Pos);
		}

		Data->BigVec = BigPos;
		Data->SmallVec = SmallPos;

		Xfile.Mesh.lpMesh->UnlockVertexBuffer();

		MeshDataList[FileName] = Data;
	}
	else {
		Data = MeshDataList[FileName];
	}

	Xfile.Data = *Data;

	return Xfile;
}
void XFileManager::AllDelete(void) {

	for (auto itr = xfileList.begin(); itr != xfileList.end(); itr++) {
		ReleaseMesh(itr->second);
		delete itr->second;
	}
	xfileList.clear();


	for (auto itr = MeshDataList.begin(); itr != MeshDataList.end(); itr++) {
		delete itr->second;
	}
	MeshDataList.clear();
}