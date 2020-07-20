#pragma once
#include<d3dx9.h>
#include<vector>
#include"Ground_Object.h"
#include"../GameSource/Count/Countdown.h"
#include"../GameSource/Count/Count.h"
#include"../Player/PlayerBase.h"
#include"Stage_Ground/Ground_Pop_New.h"

class c_GroundManager
{
public:
	c_GroundManager(C_PlayerBase *player);
	~c_GroundManager();

	// 表示
	void Draw3D(void);

	// 更新処理
	bool Update(C_PlayerBase *player);

	// 地面の当たり判定
	bool JudgNowGround(unsigned int *GroundNumber, float *Dis, bool *HitCurveGround, const D3DXMATRIX *Mat);

	// 道路の形状変更
	void SetGroundPop(const int *RoadNo);

	// 車の出現の情報作成
	void InitCarPopData(unsigned int *gNo, D3DXMATRIX *GroundMat, float *TransX,
		const unsigned int *playerGroundNum, const S_CAR_INIT_DATA *Data);

	// 弾と当たり判定
	void BulletJudg(BULLETJUDGDATA * BJD, const RAYDATA *RD, bool *HitFlg, const float *Rad);

	// 視錐台カリング
	void FrustumCulling(const S_Frustum_Vec * FV_Data);

	// 壁と球判定
	bool CapsuleJudgWall(float *SmallDis,int *hitNum, s_CarType * HitCar, const S_Capsule *c, const s_CarType * JudgCar);

	std::vector<C_Ground_Object*> GetGround(void) { return ground; }

	unsigned int GetGroundNum(void) { return ground.size(); }
	D3DXMATRIX GetGroundMat(const unsigned int* count) { return ground[*count]->GetMat(); }

	unsigned int GetWallNum(const unsigned int* gc) { return ground[*gc]->GetWallNum(); }
	D3DXMATRIX GetWallMat(const unsigned int* gc, const unsigned int *wc) { return ground[*gc]->GetWallMat(wc); }
	S_Capsule GetCapsuleWall(const unsigned int* gc, const unsigned int *wc) { return ground[*gc]->GetCapsuleWall(wc); }
	bool MeshRayJudgWall(float *Dis, const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray, const unsigned int* gc, const unsigned int * wc);

private:
	//地面のメンバ
	std::vector<C_Ground_Object*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	//外灯表示用カウントダウン
	C_Count *LightCount;

	/*地面の情報*/
	C_Ground_Pop_New* M_C_Ground_Pop;
};