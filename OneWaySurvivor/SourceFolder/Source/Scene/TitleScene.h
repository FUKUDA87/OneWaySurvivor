#pragma once
#include<d3dx9.h>
#include"SceneBase.h"
#include"../Draw/TitleParts/TitleTex.h"
#include"../Draw/TitleParts/StartTex.h"
#include"../Draw/TitleParts/TitelCamera.h"
#include"../Ground/Sky.h"
#include"../Ground/Wall.h"
#include"../Draw/2D/BulletHole.h"
#include"../Key/CMouse.h"
#include"../Key/Key.h"
#include"../Player/PlayerBody.h"
#include"../Player/PlayerA.h"
#include"../Sound/GameSoundManager.h"
#include"../Ground/Ground_Object.h"
#include"../GameSource/Option/Option.h"
#include"../Ground/GroundManager.h"

template<class T>
inline void SafeRelease(T& lpAdd)
{
	if (lpAdd != nullptr) {
		lpAdd->Release();
		lpAdd = nullptr;
	}
}
class TitleScene :public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Render2D(void);   // 2D�`��
	void Render3D(void);   // 3D�`��
	bool Update(void);     // �X�V����
	void SetCamera(void);  // �J����

private:

	Judg judg;  // ����p�̊֐��̃N���X

	c_GroundManager *groundManager;

	LPDIRECT3DTEXTURE9 Tex;
	TitleTex *titleTex;
	StartTex *startTex;
	
	//�v���C���[
	C_PlayerBase *player;
	//�v���C���[�̏��
	C_PlayerBody *PlaBodData;

	TitleCamera *camera;
	Sky *sky;
	//�e��
	std::vector<C_BulletHole*>BulHol;

	//�}�E�X
	C_Mouse *mouse;
	//�L�[
	Key key;

	//�Q�[���̏I��
	bool Game_End(void);

	c_GameSoundManager* M_C_Sound_Manager;

	//�X�e�[�W�I���V�[���ւ̈ړ�
	void Next_StageScene_Switch(void);
};