#pragma once
#include"GunBase.h"
#include"../../../Effect/EffectBase.h"
#include"../../../Effect/Gun/No1/Shot/Gun_No1_Shot_Effect.h"

class C_GunBullet :public C_GunBase {
public:
	C_GunBullet();
	int Get_BulletNo(void) { return BulletNo; }

	//銃の数渡し
	unsigned int Get_CategoryNum(void) { return M_Category_Data.size(); }

	//発射後のエフェクト渡し
	int GetShotEffectNum(void) { return BulletShotEffectNum; }
	c_EffectBase* GetShotEffect(const int *ec, const unsigned int *MouthNo);

	//トリガー
	bool Get_TriggerFlg(const unsigned int *MouthNo);

	void Bullet_Shot_Update(const unsigned int *MouthNo);

	//弾の変更
	void Set_Bullet_No(const int *No) { BulletNo = *No; }

protected:
	//弾の表示番号
	int BulletNo;

	int BulletShotEffectNum;
private:
	bool Judg_MouthNo(const unsigned int *MouthNo);
};