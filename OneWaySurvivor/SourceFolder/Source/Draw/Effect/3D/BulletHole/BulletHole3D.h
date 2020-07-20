#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"

class C_BulletHole3D:public c_EffectBase
{
public:
	C_BulletHole3D(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, int TypeNo);
	
	// 更新処理
	bool Update(void);
	
	// 表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);
	
private:
	S_Polygon Hole;
	//判定
	//壁判定
	void InitWall(int TypeNo);
	//地面判定
	void InitGround(int TypeNo);
	//時限
	int NowCount;

	//初期化
	void Init(void);

	//時限式
	bool CountUpdate(void);
};