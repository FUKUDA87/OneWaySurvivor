#pragma once
#include"../../Draw/Gun/Bullet/Base/Bullet_Base.h"

class C_Bullet_No2 :public C_Bullet_Base {
public:
	//弾の番号と銃口の行列
	C_Bullet_No2(const D3DXMATRIX *Mat);
	//プレイヤーが照準を合わせた時のコンストラクタ
	C_Bullet_No2(const D3DXMATRIX *Mat, const S_RayHitJudgData* RayData);
private:
	//初期化
	void Init_No2(void);
};