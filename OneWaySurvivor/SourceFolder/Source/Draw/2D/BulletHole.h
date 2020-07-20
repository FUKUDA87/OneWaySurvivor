#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Judgment.h"

class C_BulletHole {
public:
	C_BulletHole(const D3DXVECTOR2 *Pos,const float *AngZ,const D3DXVECTOR2 *ScalPos);
	C_BulletHole(const D3DXVECTOR2 *Pos, const float *AngZ, const D3DXVECTOR2 *ScalPos,int No);
	
	//������
	void InitBulHol(void);
	void InitBulHol(int No);
	//�\��
	void Draw2DBH(void);
	//�\���̍s��쐬
	D3DXMATRIX GetDrawMatBulHol(void);
protected:
	Judg judg;
private:
	CHARA2D BulHol;
};