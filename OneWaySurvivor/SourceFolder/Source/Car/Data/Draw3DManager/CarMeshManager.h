#pragma once
#include"../../../GameSource/Struct.h"
#include<stdio.h>
#include"../../../GameSource/Const.h"

class C_CarMeshManager 
{
public:
	XFILE3 GetMesh(int MeshNo);
private:
	//モデル情報探し
	bool GetMeshJudg(int MeshNo);

	char MeshName[3][100];
};