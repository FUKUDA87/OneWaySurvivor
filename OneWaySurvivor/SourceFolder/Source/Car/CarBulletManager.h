#pragma once
#include"CarGun.h"
#include"../Draw/Gun/Bullet/Base/Bullet_Base.h"
#include"../GameSource/Count/Count.h"

class C_CarBulletManager :public C_CarGun {
public:
	~C_CarBulletManager();

	//移動量ずらし
	void MoveVecBullet(void);

	//トリガー
	virtual void Shot(void);

	//更新
	bool UpdateBullet(void);

	//弾数渡し
	unsigned int GetBulletNum(void) { return bullet.size(); }

	// 弾の当たり判定の情報準備
	void GetBulletMoveData(BULLETJUDGDATA * Bullet, RAYDATA * BulletRay, const unsigned int *bc);

	//弾が壁と地面の判定をするかFlg渡し
	bool GetBulletGroWalJudgFlg(const unsigned int *BulletNo);

	//弾が壁と地面の判定をするかFlg代入
	void SetBulletGroWalJudgFlg(const unsigned int *BulletNo, const bool *Flg);

	//ダメージ数渡し
	int GetBulletDamage(const unsigned int *NowBulletNo) { return bullet[*NowBulletNo]->Get_S_BULLET().Damage; }

	//ひとつ削除
	void DeleteBullet(unsigned int *NowBulletNo);
protected:
	std::vector<C_Bullet_Base*>bullet;
	
	void ShotEffect(const unsigned int *gc,const unsigned int *mc);

	//弾の更新
	bool Update_ALL_Bullet(void);

	//全消し
	void AllDelete(void);

	//その番号の弾があるか判定
	bool Bullet_NoJudg(const unsigned int *NowBulletNo);

	//表示行列渡し

	//位置行列渡し
	D3DXMATRIX Get_Bullet_Mat(const unsigned int *BulletNo);

	//トリガー２

	//MoveVec入れ

	//表示
	void Draw_Bullet(const D3DXVECTOR3 *CameraPos);
};