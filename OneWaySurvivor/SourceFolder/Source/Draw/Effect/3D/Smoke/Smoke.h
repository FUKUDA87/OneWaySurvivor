#pragma once
#include<d3dx9.h>
#include"../../../../GameSource/Struct.h"
#include"../../EffectBase.h"
#include"../../../../GameSource/Count/CountBase.h"

class c_Smoke:public c_EffectBase {
public:
	c_Smoke(const int *CarNo,const D3DXMATRIX *Mat, const float *HpPer, const int *NowHp);
	~c_Smoke();

	// 更新処理
	bool Update(const s_CarEffectUpdateData *updateData);
	
	//表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);

private:
	S_Polygon smokePol;
	//時限削除用
	C_CountBase *count;

	// 煙の種類
	int Draw_No;

	//表示方法の構造体
	S_Smoke smoke;

	//透明度のアップデート
	void Update_Alpha(void);
	//乱数の数値作成
	float RandPlus(const int *Num);
	//ポリゴンサイズの変化
	float GetPolSize(void);

	// 煙の濃さ
	int InitDrawNo(const float *HpPer, const int *NowHp);
};