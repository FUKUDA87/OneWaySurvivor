#pragma once
#include"HpbarBase.h"
#include"../../GameSource/Struct.h"

class C_HpbarDraw
{
public:
	~C_HpbarDraw();

	// èâä˙âª
	void Init(C_HpbarBase* InitHpBase);

	// 2Dï\é¶
	void Draw2D(const CHARABASE *CharaBase);
	// 3Dï\é¶
	void Draw3D(const CHARABASE *CharaBase, const D3DXMATRIX *Mat
		,const D3DXVECTOR3 *CamPos,const D3DXVECTOR3 *ScalPos);
private:
	C_HpbarBase *HpbarBase;

	// çÌèú
	void Delete(void);
};