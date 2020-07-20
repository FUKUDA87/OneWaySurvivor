#pragma once
#include"CarGun.h"
#include"../Draw/Gun/Bullet/Base/Bullet_Base.h"
#include"../GameSource/Count/Count.h"

class C_CarBulletManager :public C_CarGun {
public:
	~C_CarBulletManager();

	//�ړ��ʂ��炵
	void MoveVecBullet(void);

	//�g���K�[
	virtual void Shot(void);

	//�X�V
	bool UpdateBullet(void);

	//�e���n��
	unsigned int GetBulletNum(void) { return bullet.size(); }

	// �e�̓����蔻��̏�񏀔�
	void GetBulletMoveData(BULLETJUDGDATA * Bullet, RAYDATA * BulletRay, const unsigned int *bc);

	//�e���ǂƒn�ʂ̔�������邩Flg�n��
	bool GetBulletGroWalJudgFlg(const unsigned int *BulletNo);

	//�e���ǂƒn�ʂ̔�������邩Flg���
	void SetBulletGroWalJudgFlg(const unsigned int *BulletNo, const bool *Flg);

	//�_���[�W���n��
	int GetBulletDamage(const unsigned int *NowBulletNo) { return bullet[*NowBulletNo]->Get_S_BULLET().Damage; }

	//�ЂƂ폜
	void DeleteBullet(unsigned int *NowBulletNo);
protected:
	std::vector<C_Bullet_Base*>bullet;
	
	void ShotEffect(const unsigned int *gc,const unsigned int *mc);

	//�e�̍X�V
	bool Update_ALL_Bullet(void);

	//�S����
	void AllDelete(void);

	//���̔ԍ��̒e�����邩����
	bool Bullet_NoJudg(const unsigned int *NowBulletNo);

	//�\���s��n��

	//�ʒu�s��n��
	D3DXMATRIX Get_Bullet_Mat(const unsigned int *BulletNo);

	//�g���K�[�Q

	//MoveVec����

	//�\��
	void Draw_Bullet(const D3DXVECTOR3 *CameraPos);
};