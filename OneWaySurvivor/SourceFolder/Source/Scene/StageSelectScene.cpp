#include"StageSelectScene.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"../Fade/Fade.h"

extern SceneManager sceneManager;
extern C_Fade fade;
extern C_Option option;

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight
#define GameNo 2
#define TitleNo 1

StageSelectScene::StageSelectScene()
{
	
	// �t�F�[�h�C���̊J�n
	fade.StartFadein();

	Init_New();

	mouse = new C_Mouse();
	mouse->ChaDrawFlg(true);
	sky = new StageSky();

	//�v���C���[�̏������O�ɏ�����
	PlayerBody = new C_PlayerBody();

	car = new StageCar(&PlayerBody->GetPData());
	cam = new StageCam();
	modoru = new Modoru();

	key.Init();

	//�T�E���h�̏�����
	int BGMVolume = option.GetOptionData().BGMVolume, SEVolume = option.GetOptionData().SEVolume;
	M_C_Sound_Manager = new c_GameSoundManager(&BGMVolume, &SEVolume);


	//�I�����[�h�̏������̑O�ɏ�����
	Ok = new C_OK(&D3DXVECTOR2(1.1f, 1.1f), &D3DXVECTOR2(1280.0f/2.0f, 720.0f*0.93f), &D3DXVECTOR2(0.25f, 0.11f));

	//�Ԃ̕\���̖߂��p�Z�b�g
	BodyData_Init = car->Get_BODYDATA();

	//�I�����[�h�̏�����
	InitStaSel();

	M_CarSet = new C_CarSet();

	GameScene_DebugFlg = false;

	int No = 3;
	M_C_Sound_Manager->BGMStart(&No);

	S_OptionData optionData = option.GetOptionData();
	optionChange = new C_OptionChange(&optionData.BGMVolume, &optionData.SEVolume);

}

StageSelectScene::~StageSelectScene()
{
	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Reset();
		delete M_C_Sound_Manager;
	}

	delete sky;
	delete car;
	delete cam;
	delete modoru;

	//�}�E�X�̍폜
	delete mouse;

	DeleteCarSel();

	DeleteStaSel();

	//�v���C���[�̏��폜
	delete PlayerBody;
	//Ok�{�^���̍폜
	delete Ok;

	EndFlg = false;

	if (M_CarSet != nullptr) {
		delete M_CarSet;
	}

	if (M_C_Garage_Stand != nullptr) {
		delete M_C_Garage_Stand;
	}

	if (optionChange != nullptr)delete optionChange;

	// �I�v�V����
	option.Write();

}

void StageSelectScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	Draw2D_Normal();

	// �`��I��
	lpSprite->End();

	M_CarSet->DrawTxt();
}

void StageSelectScene::Render3D(void)
{
	M_CarSet->Draw3D(&cam->GetPos());

	//�X�e�[�W�O

	//�K���[�W
	sky->Draw();

	if (M_C_Garage_Stand != nullptr) {
		M_C_Garage_Stand->Draw_Garage_Stand(&cam->GetPos());
	}

	Draw3D_Normal();
}

bool StageSelectScene::Update(void)
{
	if (Change_TitleScene() != true)return false;

	if (M_C_Sound_Manager != nullptr) {

		S_OptionData l_OptionData = option.GetOptionData();

		M_C_Sound_Manager->UpdateVolume(&l_OptionData.BGMVolume, &l_OptionData.SEVolume);

		M_C_Sound_Manager->Update();

		M_C_Sound_Manager->New();
	}

	mouse->Update();

	//�t�F�[�h�̃A�b�v�f�[�g
	if (fade.Update() == true) {
		//�L�[�̖��͉�

	}
	else {
		if (fade.GetMoveEndFlg() == true) {
			sceneManager.changeScene(fade.GetNextScene());
			return false;
		}
	}

	ChangeMode_Car();

	bool keyFlg = key.LClickF();
	S_OptionData optionData = option.GetOptionData();
	if (optionChange != nullptr)optionChange->Update(&keyFlg, &optionData.BGMVolume, &optionData.SEVolume);
	option.setOptionData(&optionData);

	Update_Normal(&keyFlg);

	Update_Car();

	car->Update();

	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.0f, 2.0f, 0.0f);
	sky->Update(&tmp);
	return true;
}

void StageSelectScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&cam->GetPos(),//�J�����̈ʒu
		&cam->GetLook(),// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void StageSelectScene::DeleteCarSel(void)
{
	if (CarSel.size() <= 0) return;

	for (unsigned int c = 0; c < CarSel.size(); c++) {
		delete CarSel[c];
		CarSel.erase(CarSel.begin() + c);
		c--;
	}
}

void StageSelectScene::DeleteStaSel(void)
{
	if (stage.size() <= 0) return;
	
	for (unsigned int i = 0; i < stage.size(); i++) {
		delete stage[i];
		stage.erase(stage.begin() + i);
		i--;
	}
}

void StageSelectScene::ChangeMode(const bool * KeyFlg)
{
	//�X�e�[�W�I�����[�h
	if (StageModeFlg == true) {
		StageSelectMode(KeyFlg);
		return;
	}
	//�ԑI�����[�h
	if (CarModeFlg == true) {
		CarSelectMode(KeyFlg);
		return;
	}
}

bool StageSelectScene::StageSelectMode(const bool * KeyFlg)
{
	//�߂�{�^��
	if (modoru->UpdateSu() == false) {
		mouse->SetTouchFlg();
		if (*KeyFlg == true) {
			fade.SetNextScene(co_TitleScene, true);
			StageModeFlg = false;
			CarModeFlg = false;
			return true;
		}
	}
	//�X�e�[�W�I���{�^��
	if (stage.size() > 0) {
		for (unsigned int s = 0; s < stage.size(); s++) {
			if (stage[s]->UpdateSu() == false) {
				mouse->SetTouchFlg();
				if (*KeyFlg == true) {
					fade.SetNextStageNo(stage[s]->GetStageNo());
					InitCarSel();
					return true;
				}
			}
		}
	}
	return true;
}

void StageSelectScene::InitStaSel(void)
{
	//�t���O�̃Z�b�g
	StageModeFlg = true;
	CarModeFlg = false;

	//�\���̍폜
	DeleteCarSel();
	//Ok�{�^���̕\���Z�b�g
	Ok->SetDrawFlg(false);

	//�X�e�[�W�I���A�C�R���쐬
	for (int s = 0; s < 1; s++) {
		stage.push_back(new StageTex(s + 1, D3DXVECTOR2((float)SCRW / 6.0f*(float)(s + 1), (float)SCRH / 4.0f)));
	}

	//�Ԃ̕\���߂�
	car->SetBody(&BodyData_Init);

	//�f�[�^�ɃZ�b�g
	PlayerBody->SetPData(&car->Get_BODYDATA());
}

bool StageSelectScene::CarSelectMode(const bool * KeyFlg)
{
	//�߂�{�^��
	if (modoru->UpdateSu() == false) {
		mouse->SetTouchFlg();
		if (*KeyFlg == true) {
			InitStaSel();
			return true;
		}
	}
	//�ԃ{�^��
	if (CarSel.size() > 0) {
		int tNo;
		for (auto && c : CarSel) {
			tNo = c->Touch();
			if (tNo > 0) {
				if (*KeyFlg == true) {
					if (tNo == 1) {
						int No = c->GetNo() - 1;
						ChangeCar(&No);
						c->UpdateNo(&No);
						return true;
					}
					if (tNo == 2) {
						int No = c->GetNo() + 1;
						ChangeCar(&No);
						c->UpdateNo(&No);
						return true;
					}
				}
			}
		}
	}
	//Ok�{�^��
	if (*KeyFlg == true) {
		if (Ok->Touch() == true) {
			Set_GameScene_DebugFlg();
			fade.SetNextStageNo(&GameScene_DebugFlg);
			fade.SetNextScene(co_GameScene, false);
			return true;
		}
	}

	return true;
}

void StageSelectScene::InitCarSel(void)
{
	//�t���O�̃Z�b�g
	StageModeFlg = false;
	CarModeFlg = true;

	DeleteStaSel();
	//Ok�{�^���̕\���Z�b�g
	Ok->SetDrawFlg(true);

	//�I���̏�����
	CarSel.push_back(new C_CarSelect(
		&D3DXVECTOR2(1280.0f / 5.0f*4.0f, 720.0f / 4.0f*3.0f), &D3DXVECTOR2(0.15f, 0.11f), &D3DXVECTOR2(0.33f, 0.31f), &D3DXVECTOR2(-100.0f, 0.0f), &D3DXVECTOR2(0.85f, 0.85f)
	));
	int No = PlayerBody->GetPData().CarBodyNo;
	CarSel[CarSel.size() - 1]->UpdateNo(&No);

	//�Ԃ̕\���̖߂��p�Z�b�g
	BodyData_Init = car->Get_BODYDATA();

}

void StageSelectScene::ChangeCar(int * No)
{
	//���b�V���̎�ޕς�
	if (*No > 2)*No = 1;
	if (*No < 1)*No = 2;

	BODYDATA pData = PlayerBody->GetPData();
	pData.CarBodyNo = *No;
	//�Ԃɔ��f
	car->SetBody(&pData);

	//�f�[�^�ɃZ�b�g
	PlayerBody->SetPData(&car->Get_BODYDATA());

}

void StageSelectScene::ChangeMode_Car(void)
{
	if (fade.GetMoveFlg() != false)return;

	if (CarModeFlg != true)return;

	if (key.RETURNKeyF() != true)return;

	if (GetAsyncKeyState('8') & 0x8000) {
		if (GetAsyncKeyState('9') & 0x8000) {
			M_CarSet->ChangeMode(true);
			if (M_CarSet->GetModeFlg() == true)mouse->Init();
		}
	}
}

bool StageSelectScene::Update_Normal(const bool * KeyFlg)
{
	if (M_CarSet->GetModeFlg() != false)return false;

	ChangeMode(KeyFlg);

	D3DXMATRIX cTmp;
	D3DXMatrixTranslation(&cTmp, 0.0f, 1.0f, 0.0f);
	cam->Update(car->GetMatCar(), cTmp, true);

	return false;
}

bool StageSelectScene::Update_Car(void)
{
	if (M_CarSet->GetModeFlg() != true)return false;

	D3DXVECTOR3 l_Pos = M_CarSet->GetPartsPos();
	if (key.AKey() == true)l_Pos.x -= M_CarSet->GetUp();
	if (key.FKey() == true)l_Pos.x += M_CarSet->GetUp();

	if (key.WKey() == true)l_Pos.y += M_CarSet->GetUp();
	if (key.SKey() == true)l_Pos.y -= M_CarSet->GetUp();

	if (key.EKey() == true)l_Pos.z += M_CarSet->GetUp();
	if (key.DKey() == true)l_Pos.z -= M_CarSet->GetUp();
	M_CarSet->SetPartsPos(&l_Pos);

	if (key.XKeyF() == true)M_CarSet->ChangeCar();

	cam->UpdateCar(mouse);

	mouse->Init();

	float y = cam->GetHeight();

	if (key.TKey() == true)y += M_CarSet->GetUp();
	if (key.GKey() == true)y -= M_CarSet->GetUp();

	cam->SetHeight(&y);

	if (key.ZKeyF() == true)M_CarSet->ChangePartsMeshFlg(true);
	if (key.CKeyF() == true)M_CarSet->ChangePartsMesh(true);

	//�p�[�c���W�ύX��
	if (M_CarSet->Get_Mesh_JudgFlg() != Co_Draw_Mesh)return false;
	l_Pos = M_CarSet->GetPartsPos();
	float l_Dis;
	Judg judg;
	if (judg.RayJudg_Mesh(&l_Pos, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &sky->GetDrawSkyMat(), sky->GetSkyMesh(), &l_Dis) == true) {
		D3DXVECTOR3 l_Pos2 = l_Pos + D3DXVECTOR3(0.0f, -1.0f, 0.0f)*l_Dis;
		
		D3DXMATRIX Mat;
		D3DXMatrixTranslation(&Mat, l_Pos.x, l_Pos.y, l_Pos.z);
		if (judg.RayJudg_Mesh(&l_Pos2, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &Mat, M_CarSet->Get_Mesh(), &l_Dis) == true) {
			l_Pos2 = l_Pos2 + D3DXVECTOR3(0.0f, 1.0f, 0.0f)*l_Dis;

			M_CarSet->GroundSize(&l_Pos2.y);
		}
	}

	return false;
}

void StageSelectScene::Draw3D_Normal(void)
{
	if (M_CarSet->GetModeFlg() != false)return;

	//�ԑ�
	car->Draw3D(&cam->GetPos());
}

void StageSelectScene::Draw2D_Normal(void)
{
	if (M_CarSet->GetModeFlg() != false)return;

	//�߂�
	modoru->DrawSu();
	//�X�e�[�W
	if (stage.size() > 0) {
		for (unsigned int s = 0; s < stage.size(); s++) {
			stage[s]->DrawSu();
		}
	}

	if (CarSel.size() > 0) {
		for (unsigned int c = 0; c < CarSel.size(); c++) {
			CarSel[c]->Draw2DAll();
		}
	}

	Ok->Draw2DOK();

	if (optionChange != nullptr)optionChange->Draw2D();

	fade.Draw();
	mouse->Draw2D();
}

bool StageSelectScene::Change_TitleScene(void)
{
	if (key.EscapeKey_F() == true) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}

	return true;
}

void StageSelectScene::Car_Ground_Vec(void)
{
}

void StageSelectScene::Init_New(void)
{
	//M_C_Garage_Stand = new C_Stage_Room_Stand(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Car_Stand_O_1.x");
}

void StageSelectScene::Set_GameScene_DebugFlg(void)
{
	if (key.Num7Key() != true)return;

	if (key.Num8Key() != true)return;

	if (key.Num9Key() != true)return;

	GameScene_DebugFlg = true;
}