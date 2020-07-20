#pragma once
#include"CarParts.h"
#include"../Draw/Gun/Draw/NewGun/GunLaser.h"
#include"../Draw/Gun/Draw/Move/GunMoveBase_A.h"

class C_CarGun :public C_CarParts {
public:
	~C_CarGun();

	//�e�����˂���e�̕ύX
	void Set_Gun_Bullet_No(const unsigned int *M_GunNo, const int *BulletNo);

	//�e�̈���������
	void Set_Gun_Trigger(const unsigned int *GunNo, const bool *TriggerFlg);

	//�e�̐��n��
	unsigned int Get_Gun_Num(void) { return gun.size(); }

	//�\���̏e�̏��n��
	S_GUN_DATA Get_Gun_Data(const unsigned int *DarwGunNo);

	//���C�̔������
	void Set_Ray_Hit_Flg(const unsigned int *DrawGunNo, const bool *Flg) { gun[*DrawGunNo]->Set_Ray_Hit_Flg(Flg); }
	
	//���[�U�[�̒�������
	void Set_Ray_Dis(const unsigned int *M_GunNo, const float *Dis);

	// ���C����
	void RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad);

	//�e��Hp�����炷����
	bool Damage_Gun(const unsigned int *M_GunNo, const int *Damage);

protected:
	//�S�Ă̏e�̍폜
	void AllDelete_Gun(void);

	//�e�̓�����n��
	virtual C_GunMoveBase_A *Get_GunMove(const int *MoveNo);

	//�e�̓������v���C���[�̑���ɂ���B
	virtual void Set_GunMove_Player(const unsigned int *GunNo);

	std::vector<C_GunLaser*>gun;

	//�p�[�c�̏�����
	void New_Set_Car_Parts(const BODYDATA *CarData);
	void New_Set_Car_Parts(const int *CarNo, std::vector<C_Parts_Set_Data*>M_Set_Data);

	//�e�̂�����
	virtual void New_Car_Parts_Gun(const BODYDATA *CarData);
	virtual void New_Car_Parts_Gun(std::vector<C_Parts_Set_Data*>M_Set_Data);

	// ���C����
	void RayJudgGun(BULLETJUDGDATA * BJD, const D3DXVECTOR3 *Pos, const int *CarType, const unsigned int *cc, const D3DXVECTOR3 *Ray);


	//�\��
	void Draw_Gun(const D3DXVECTOR3 *CameraPos);
	//�X�V
	void Update_Gun(void);

	//�X�^���h�ƃW���C���g�̍s��
	D3DXMATRIX Get_Joint_Mat(void);
	D3DXMATRIX Get_Joint_Mat(const int *JointNo);

	/*
	�����蔻��
	*/
	//�\���p�[�c���n��
	unsigned int Get_Gun_Draw_Parts_Num(const unsigned int *M_GunNo) {
		return gun[*M_GunNo]->Get_Draw_Parts_Num();
	}

	//�|���S��Flg
	int Get_Gun_Draw_Parts_Draw_JudgFlg(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//�|���S���̒��_�n��
	D3DXVECTOR3 Get_Gun_Draw_Parts_Pol_Pos(const unsigned int *M_GunNo, const unsigned int *PartsNo, const int *PolNo);

	//���b�V���n��
	LPD3DXMESH Get_Gun_Draw_Parts_Mesh(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//�P�ʍs��̊m�F
	bool Get_Gun_Draw_Parts_Iden_Flg(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//�\���̍s��n��
	D3DXMATRIX Get_Gun_Draw_Parts_Draw_Mat(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//�e�Ƀ��C���΂��Ă������̊m�F
	bool Ray_Judg_Gun_Flg(const unsigned int *M_GunNo);



private:

	/*�֐�*/

	//�e�̍폜
	void Delete_Gun(unsigned int *GunNo);

	//�e�̔ԍ������݂��邩����
	bool Judg_GunNo(const unsigned int *GunNo);
};