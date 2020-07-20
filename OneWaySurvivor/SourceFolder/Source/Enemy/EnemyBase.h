#pragma once
#include"../Car/CarBulletManager.h"
#include"../Enemy/Vector.h"

class C_EnemyBase :public C_CarBulletManager {
public:
	C_EnemyBase();
	~C_EnemyBase();

	//アップデート
	bool UpdateCar(void);

	//表示
	void Draw3D(const D3DXVECTOR3 *CamPos);
	void Draw2D(void);

	//矢印作成に必要な情報の取得とアップデート
	void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport, const D3DXVECTOR3 *CameraPos);

	//エネミーの存在削除渡し
	bool GetDeleFlg(void);

	//パーツの位置調整
	void SetParts(std::vector<C_Ground_Object*>ground);

	//ボスなのか確認
	bool Get_BossFlg(void) { return M_BossFlg; }

	// カプセル判定(CarBaseOverride)
	bool capsuleJudg(float *sd, int *hitNum, const S_Capsule *c, const bool *ForMoveJudgFlg);

protected:
	//矢印
	Vector *Vect;

	D3DXVECTOR3 Pos2D;

	int m_EnemyNo;

	//ボスであるかの確認Flg
	bool M_BossFlg;

	
private:
	//初期化
	void InitEnemy(void);
};