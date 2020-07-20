#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Judgment.h"
#include"../../../GameSource/Struct.h"

class C_LaserBase2 {
public:
	C_LaserBase2(const int *TexNo);
	//Mat,TransPos,PolSize,CamPos,Dis,DrawFlg
	virtual void Draw3DAll(const D3DXMATRIX* Mat, const D3DXVECTOR3*TransPos, const float*PolSize, const D3DXVECTOR3*CamPos, const float*Dis, const bool*DrawFlg)=0;
	void SetTexNo(const int *TexNo);
protected:
	void GetHitPos(D3DXVECTOR3*StartPos, D3DXVECTOR3*HitPos, const D3DXMATRIX* Mat, const D3DXVECTOR3*TransPos, const float*Dis);
	void Init(void);
	Judg judg;
	VERTEX v[4];
	TEXTURE m_LaserTex;
private:

};