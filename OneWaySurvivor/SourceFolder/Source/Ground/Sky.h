#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

#ifndef Sky_H
#define Sky_H

class Sky{
protected:
	Object3D sky;
public:
	void Init();
	Sky();
	bool Update(const D3DXMATRIX *PM);
	void Draw();

	LPD3DXMESH GetSkyMesh(void) {
		return sky.Mesh.lpMesh;
	}

	D3DXMATRIX GetDrawSkyMat(void) {
		D3DXMATRIX Mat = sky.Base.Scal*sky.Base.Mat;
		return Mat;
	}

};

#endif // !Sky_H
