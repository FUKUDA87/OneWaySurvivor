#pragma once
#include<d3dx9.h>
#include<string>
#include<map>
#include"../GameSource/Struct.h"

class XFileManager 
{
public:
	~XFileManager();
	XFILE GetMesh(std::string FileName);
	XFILE_B GetMeshB(std::string FileName);
	void AllDelete(void);
private:
	std::map<std::string, XFILE*>xfileList;
	std::map<std::string, S_MeshData*>MeshDataList;
};

