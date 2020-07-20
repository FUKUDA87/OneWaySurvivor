#pragma once
#include"SceneBase.h"
#include<vector>
#include<d3dx9.h>

//�\��
#include"../Draw/TitleParts/TitleSky.h"
#include"../Draw/StageParts/StageCar.h"
#include"../Draw/StageParts/StageCamera.h"
#include"../Draw/2D/modoru.h"
#include"../Draw/StageParts/StageTex.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../Draw/StageParts/CarSelect.h"
#include"../Player/PlayerBody.h"
#include"../Draw/StageParts/OkButton.h"
#include"../Draw/StageParts/CarSet.h"
#include"../Draw/StageParts/Stage_Room.h"
#include"../Sound/GameSoundManager.h"
#include"../GameSource/Option/Option.h"
#include"../Draw/Button/Option/OptionChange.h"


class StageSelectScene :public SceneBase {
public:
	StageSelectScene();
	~StageSelectScene();
	void Render2D(void);
	void Render3D(void);
	bool Update(void);
	void SetCamera(void);

protected:

	//�ԑI���̍폜
	void DeleteCarSel(void);

	//�X�e�[�W�I���̍폜
	void DeleteStaSel(void);

	//�I��-----------------------------------------------------------------
	//�I�����[�h�ؑ�
	void ChangeMode(const bool *KeyFlg);
	//�X�e�[�W�I�����[�h
	bool StageSelectMode(const bool *KeyFlg);
	void InitStaSel(void);
	//�Ԑ؂�ւ����[�h
	bool CarSelectMode(const bool *KeyFlg);
	void InitCarSel(void);

	//�Ԃ̃{�f�B�ς�
	void ChangeCar(int *No);

	//�`�F���WMode
	void ChangeMode_Car(void);

	//�ʏ탂�[�h�A�b�v�f�[�g
	bool Update_Normal(const bool *KeyFlg);
	//�J�X�^�����[�h�A�b�v�f�[�g
	bool Update_Car(void);
	//�\���RD�̒ʏ탂�[�h
	void Draw3D_Normal(void);
	//�\���QD�̒ʏ탂�[�h
	void Draw2D_Normal(void);

	//�^�C�g���V�[���ɋ����ړ�
	bool Change_TitleScene(void);

private:

	//�n�ʂɗ��l�ɒ��ׂ�
	void Car_Ground_Vec(void);

	void Init_New(void);

	StageSky *sky;
	//�v���C���[�̏��
	C_PlayerBody *PlayerBody;
	StageCar *car;

	StageCam *cam;
	Modoru *modoru;
	std::vector<StageTex*>stage;

	//�}�E�X
	C_Mouse *mouse;
	//�L�[
	C_KeyTrue key;

	//�I������
	bool EndFlg;


	//�I��\��
	std::vector<C_CarSelect*>CarSel;

	//�I�����[�hFlg
	bool StageModeFlg;
	bool CarModeFlg;

	//OK�{�^��
	C_OK *Ok;

	C_CarSet *M_CarSet;

	BODYDATA BodyData_Init;

	//�Ԃ̃X�^���h
	C_Stage_Room_Stand *M_C_Garage_Stand;

	//�Q�[���V�[���Ńf�o�b�O���[�h�ɂ���
	bool GameScene_DebugFlg;
	//�f�o�b�O���[�h�ɐ؂�ւ�
	void Set_GameScene_DebugFlg(void);

	//
	c_GameSoundManager* M_C_Sound_Manager;

	C_OptionChange *optionChange;
};