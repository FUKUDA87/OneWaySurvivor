#pragma once
#include"../MeshBase.h"

class C_Bullet_MeshDraw :public C_MeshBase {
public:
	C_Bullet_MeshDraw(const int *BulletMeshNo);

	//•\Ž¦
	void Draw(const D3DXMATRIX *Mat);
protected:

private:

};