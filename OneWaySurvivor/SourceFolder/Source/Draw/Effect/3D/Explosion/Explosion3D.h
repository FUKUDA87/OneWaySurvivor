#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"
#include"../../../../GameSource/Struct.h"
#include"../../../../GameSource/Count/Countdown.h"

class c_Explosion3D:public c_EffectBase {
public:
	c_Explosion3D(const D3DXMATRIX *Mat);
	~c_Explosion3D();
	
	// çXêVèàóù
	virtual bool Update(void);
	
	// ï\é¶
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

private:
	S_Polygon expl;
	
	Cou *cou;
	void Init();
};