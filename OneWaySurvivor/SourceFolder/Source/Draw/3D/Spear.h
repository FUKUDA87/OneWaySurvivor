#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class Spear {
protected:
	Object3D s, e,v;
public:
	void Init();
	Spear() { Init(); };
	Spear(D3DXMATRIX TmpStart, D3DXMATRIX TmpEnd);
	~Spear() {};
	void Update(D3DXMATRIX Mat, bool DrawFlg);
	void Draw3D(void);
	void Draw3D(D3DXMATRIX Mat);
	void Draw3DV(D3DXMATRIX Mat);
};