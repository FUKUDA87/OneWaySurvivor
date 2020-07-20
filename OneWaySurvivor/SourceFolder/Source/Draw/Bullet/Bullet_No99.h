#pragma once
#include"Bullet_No2.h"

class C_Bullet_No99 :public C_Bullet_No2 {
public:
	//弾の番号と銃口の行列
	C_Bullet_No99(const D3DXMATRIX *Mat);
	//プレイヤーが照準を合わせた時のコンストラクタ
	C_Bullet_No99(const D3DXMATRIX *Mat, const S_RayHitJudgData* RayData);
protected:
	void Init_99(void);
};