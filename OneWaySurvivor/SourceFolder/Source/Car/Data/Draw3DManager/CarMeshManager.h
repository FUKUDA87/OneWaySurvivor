#pragma once
#include"../../../GameSource/Struct.h"
#include<stdio.h>
#include"../../../GameSource/Const.h"

class C_CarMeshManager 
{
public:
	XFILE3 GetMesh(int MeshNo);
private:
	//ƒ‚ƒfƒ‹î•ñ’T‚µ
	bool GetMeshJudg(int MeshNo);

	char MeshName[3][100];
};