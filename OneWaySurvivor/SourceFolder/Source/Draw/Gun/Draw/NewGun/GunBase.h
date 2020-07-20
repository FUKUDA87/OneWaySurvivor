#pragma once
#include<d3dx9.h>
#include"../../../../GameSource/Struct.h"
#include"../../../../GameSource/CharaBase.h"
#include"../Move/GunMoveBase_A.h"
#include"../Parts/GunPartsDraw.h"
#include"../Parts/Gun_Parts_Category.h"
#include"../Trigger/Gun_Trigger_Base.h"
#include<vector>

class C_GunBase:public C_CharaBase {
public:
	C_GunBase();
	~C_GunBase();

	//�X�V����
	bool Update(S_GUN_UPDATE_DATA* s_Update);

	//�\������
	virtual void Draw(const D3DXVECTOR3* CameraPos);

	//�e�̓����n��
	S_GUN_DATA Get_S_GUN_DATA(void) {
		return M_S_GunData;
	}

	//�e�̓����̃R���X�g���N�^
	void New_GunMove(C_GunMoveBase_A *s_GunMove);

	//�e�����n��
	int Get_GunMouth_Num(void);

	//�e���n��
	D3DXMATRIX Get_GunMouth_Mat(const unsigned int *MouthNo);

	//�������̍X�V
	bool Update_Trigger(const bool *TriggerFlg);

	//�e���̃`�F���W
	bool Gun_Mouth_Change(void);

	//���C�̔������
	void Set_Ray_Hit_Flg(const bool *Flg) {
		M_S_GunData.Ray_Hit_Flg = *Flg;
	}

	//���ː��̃��Z�b�g
	void Init_Departure_Num(void);

	//�e�̕\���̃T�C�Y�ύX
	void Set_ScalPos(const D3DXVECTOR3* s_ScalPos);

	/*
	�����蔻��
	*/
	//�\���p�[�c���n��
	unsigned int Get_Draw_Parts_Num(void) {
		return M_GunParts.size();
	}

	//�|���S��Flg
	int Get_Draw_Parts_Draw_JudgFlg(const unsigned int *PartsNo);

	//�|���S���̒��_�n��
	D3DXVECTOR3 Get_Draw_Parts_Pol_Pos(const unsigned int *PartsNo, const int *PolNo);

	//���b�V���n��
	LPD3DXMESH Get_Draw_Parts_Mesh(const unsigned int *PartsNo);

	//�P�ʍs��̊m�F
	bool Get_Draw_Parts_Iden_Flg(const unsigned int *PartsNo);

	//�\���̍s��n��
	D3DXMATRIX Get_Draw_Parts_Draw_Mat(const unsigned int *PartsNo);

protected:
	/*�ϐ�*/

	//�e�̓����̕ϐ�
	C_GunMoveBase_A *M_GunMove;

	//�e�̏��̕ϐ�
	S_GUN_DATA M_S_GunData;

	//�e�̕\���p�[�c
	std::vector<C_PartsDraw_Gun*>M_GunParts;

	//�e�̃J�e�S���[
	std::vector<C_Gun_Parts_Category*>M_Category_Data;

	//������
	C_Gun_Trigger_Base* M_C_Trigger;

	//�\���̏���
	virtual void Draw_Gun(const D3DXVECTOR3* CameraPos);

private:

	//�e�̓����̍폜
	void Delete_GunMove(void);

	//�e�̃p�[�c�̕\��
	void Draw_GunParts(const D3DXVECTOR3 *CameraPos);

	//���[�g�̊m�F�̊֐�
	void Judg_Rate(void);
};