#pragma once
#include"GunBase.h"
#include"../../../Effect/EffectBase.h"
#include"../../../Effect/Gun/No1/Shot/Gun_No1_Shot_Effect.h"

class C_GunBullet :public C_GunBase {
public:
	C_GunBullet();
	int Get_BulletNo(void) { return BulletNo; }

	//�e�̐��n��
	unsigned int Get_CategoryNum(void) { return M_Category_Data.size(); }

	//���ˌ�̃G�t�F�N�g�n��
	int GetShotEffectNum(void) { return BulletShotEffectNum; }
	c_EffectBase* GetShotEffect(const int *ec, const unsigned int *MouthNo);

	//�g���K�[
	bool Get_TriggerFlg(const unsigned int *MouthNo);

	void Bullet_Shot_Update(const unsigned int *MouthNo);

	//�e�̕ύX
	void Set_Bullet_No(const int *No) { BulletNo = *No; }

protected:
	//�e�̕\���ԍ�
	int BulletNo;

	int BulletShotEffectNum;
private:
	bool Judg_MouthNo(const unsigned int *MouthNo);
};