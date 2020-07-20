#include "CarMeshManager.h"
#include"../../../MaterialManager/XfileManager.h"

extern XFileManager xfileManager;

XFILE3 C_CarMeshManager::GetMesh(int MeshNo)
{
	//検索
	if (GetMeshJudg(MeshNo) == false) {
		//検索失敗用
		sprintf_s(MeshName[0], sizeof(MeshName[0]), "car1.x");
		sprintf_s(MeshName[1], sizeof(MeshName[1]), "PlayerCar1CM3.x");
		sprintf_s(MeshName[2], sizeof(MeshName[2]), "Car_No1_Dead.x");
	}

	//メッシュのロード
	XFILE3 Mesh;
	Mesh.DrawMesh = xfileManager.GetMesh(MeshName[0]);
	Mesh.ColMod = xfileManager.GetMeshB(MeshName[1]);
	Mesh.DeadMesh = xfileManager.GetMesh(MeshName[2]);

	return Mesh;
}

bool C_CarMeshManager::GetMeshJudg(int MeshNo)
{
	//検索
	switch (MeshNo)
	{
	case CarNo1:
		sprintf_s(MeshName[0], sizeof(MeshName[0]), "car1.x");
		sprintf_s(MeshName[1], sizeof(MeshName[1]), "PlayerCar1CM3.x");
		sprintf_s(MeshName[2], sizeof(MeshName[2]), "Car_No1_Dead.x");
		return true;
		break;
	case CarNo2:
		sprintf_s(MeshName[0], sizeof(MeshName[0]), "Car3.x");
		sprintf_s(MeshName[1], sizeof(MeshName[1]), "Car3CM1.x");
		sprintf_s(MeshName[2], sizeof(MeshName[2]), "Car3.x");
		return true;
		break;
	case CarNo101:
		sprintf_s(MeshName[0], sizeof(MeshName[0]), "EnemyCar2.x");
		sprintf_s(MeshName[1], sizeof(MeshName[1]), "EnemyCar1CM2.x");
		sprintf_s(MeshName[2], sizeof(MeshName[2]), "EnemyCar1Dead.x");
		return true;
		break;
	case CarNo201:
		sprintf_s(MeshName[0], sizeof(MeshName[0]), "Car3-1.x");
		sprintf_s(MeshName[1], sizeof(MeshName[1]), "EnemyCar1CM2.x");
		sprintf_s(MeshName[2], sizeof(MeshName[2]), "EnemyCar1Dead.x");
		return true;
		break;
	}
	
	return false;
}
