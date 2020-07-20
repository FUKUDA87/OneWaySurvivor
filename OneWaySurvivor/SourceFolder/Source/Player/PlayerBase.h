#pragma once
#include"../Car/CarBulletManager.h"

class C_PlayerBase :public C_CarBulletManager {
public:
	C_PlayerBase();
	~C_PlayerBase();
	
	//�p���̃A�b�v�f�[�g
	virtual bool Update(void);

	//�p���̕\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);
	void Draw2D(void);

	float GetRadF(void) { return RadField; }
	void SetRadF(float rad) { RadField = rad; }

	//�J�[�u��Ang����
	void SetRodAngY(float Inc, bool KeyFlg);
	//CurEnd
	void SetCurRotMat(void);

	//�e�̏����ύX
	//�e�����Ɖ���Key
	bool UpdateBulPla(const bool *KeyFlg, const bool *BirthFlg, const SoundCamera *sc);

	//�J�����̍s��̃Z�b�g
	void Set_CameraMat(const D3DXMATRIX *CameraMat);

	//���C�̍��W�n��
	S_RayHitJudgData Get_Gun_Ray_Data(void) { return M_Gun_Ray_Data; }

	//���C�̏�����
	void Set_Gun_Ray_Data(const S_RayHitJudgData *Data) { M_Gun_Ray_Data = *Data; }

	//�e�̏o��
	void Shot(void);

	// ���C����
	void RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad);

private:
	
	FILE* fp;
	//�n�ʂ̕\���͈�
	float RadField;
	//�J�[�u�p�x
	float CurAng;
	D3DXMATRIX CurRotMatY;

	//���C����e�̍��W�̎擾
	S_RayHitJudgData M_Gun_Ray_Data;

	//������
	void Init_Ray_Data(void);

	//������
	void InitPlayer(void);
};