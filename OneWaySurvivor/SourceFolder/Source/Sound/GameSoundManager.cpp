#include "GameSoundManager.h"
#include"SE/Sound_2D_Gun_1.h"
#include"BGM/Sound_BGM_Manager.h"
#include"SE/Warning/Sound_Warning_Manager.h"
#include"SE/Click/Sound_Click_Manager.h"
#include"SE/SEManager/Sound_Explosion_Manager.h"
#include"SE/BulletHit/Sound_Bullet_Hit_Manager.h"

c_GameSoundManager::c_GameSoundManager(const int * g_BGMVolume, const int * g_SEVolume)
{
	UpdateVolume(g_BGMVolume, g_SEVolume);
}

c_GameSoundManager::~c_GameSoundManager()
{
	//Stop_Sound_All();

	Delete();

	BGMDelete();
}

bool c_GameSoundManager::Update()
{
	bool Flg = false;

	if (m_BGMSound != nullptr)m_BGMSound->Update(&M_CamPos, &Flg, &BGMVolume);

	if (m_SoundManager.size() < 1)return false;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (m_SoundManager[s]->Update(&M_CamPos, &Flg, &SEVolume) == false) {
			delete m_SoundManager[s];
			m_SoundManager.erase(m_SoundManager.begin() + s);
			s--;
		}
	}

	return false;
}

bool c_GameSoundManager::Update(const D3DXVECTOR3 * CamPos, const D3DXVECTOR3 * CamLook, const D3DXVECTOR3 * CamHead)
{
	M_CamPos.Pos = *CamPos;
	M_CamPos.Look = *CamLook;
	M_CamPos.Head = *CamHead;

	Update();

	return true;
}

void c_GameSoundManager::UpdateVolume(const int * g_BGMVolume, const int * g_SEVolume)
{
	BGMVolume = *g_BGMVolume;
	SEVolume = *g_SEVolume;
}

bool c_GameSoundManager::Order(const S_SOUND_DATA * M_Data)
{
	if (M_Data->Change_Type < 0)return false;

	switch (M_Data->Change_Type)
	{
	case Co_SoundNew:
		SearchNew(M_Data);
		break;
	case Co_SoundDelete:
		Delete(M_Data, true);
		break;
	case Co_SoundStart:
		Restart(M_Data);
		break;
	case Co_SoundStop:
		Stop(M_Data);
		break;
	case Co_SoundDeleteAll:
		Reset();
		Delete();
		break;
	case Co_SoundStartAll:
		Restart();
		break;
	case Co_SoundStopAll:
		Stop();
		break;
	default:
		break;
	}

	return true;
}

void c_GameSoundManager::Reset(void)
{
	BGMReset();

	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Reset();
	}
}

void c_GameSoundManager::Stop(void)
{
	BGMStop();

	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Stop();
	}
}

void c_GameSoundManager::Stop(const S_SOUND_DATA * M_Data)
{
	// BGMの検索
	if (M_Data->Sound_Type == Co_Sound_Type_2D) {
		if (M_Data->Sound_CategoryNo == Co_Sound_Category_BGM) {
			BGMStop();
			return;
		}
	}

	if (m_SoundManager.size() < 1) return;

	// 検索
	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (JudgData(M_Data, &m_SoundManager[s]->Get_Data()) == true) m_SoundManager[s]->Stop();
	}
}

void c_GameSoundManager::Restart()
{
	BGMRestart();

	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Restart(&SEVolume);
	}
}

void c_GameSoundManager::Restart(const S_SOUND_DATA * M_Data)
{
	// BGMの検索
	if (M_Data->Sound_Type == Co_Sound_Type_2D) {
		if (M_Data->Sound_CategoryNo == Co_Sound_Category_BGM) {
			BGMRestart();
			return;
		}
	}

	if (m_SoundManager.size() < 1) return;

	// 検索
	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (JudgData(M_Data, &m_SoundManager[s]->Get_Data()) == true) m_SoundManager[s]->Restart(&SEVolume);
	}
}

void c_GameSoundManager::Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos)
{
	return;

	S_SOUND_DATA Data;

	//位置の初期化
	Data.Pos = *Sound_Pos;

	//音の種類の初期化
	Data.Sound_CategoryNo = Co_Sound_Category_Bullet_Hit;

	//被弾した種類の検索
	switch (*BulletHit_Type)
	{
	case Hit_Type_Player://プレイヤーに被弾
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Enemy://敵に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Player*-1://ダメージ無効の時に被弾
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Enemy*-1://ダメージ無効の時に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Wall://壁に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Ground://地面に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	default://検索にひっかからない場合
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	}

	//被弾音の管理クラス
	C_Sound_Bullet_Hit_Manager Sound_Hit_Manager;

	//インスタンス化
	m_SoundManager.push_back(Sound_Hit_Manager.Get_Sound(&Data));

	//インスタンス化した音声を流す処理
	bool PlayFlg = true;
	m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &PlayFlg, &SEVolume);

	return;
}

void c_GameSoundManager::Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const bool * DamageFlg)
{
	//被弾音の種類
	int Type = *BulletHit_Type;

	//ダメージを受けた確認
	if (*DamageFlg != true) Type *= -1;

	//被弾音を流す処理
	Set_Bullet_Hit_Sound(&Type, Sound_Pos);
}

void c_GameSoundManager::BGMStart(const int *No)
{
	BGMDelete();

	C_Sound_BGM_Manager Manager;
	m_BGMSound = Manager.Get_BGM(No);

	bool Flg = true;

	m_BGMSound->Update(&M_CamPos, &Flg, &BGMVolume);
}

void c_GameSoundManager::BGMDelete(void)
{
	BGMReset();

	if (m_BGMSound == nullptr)return;

	delete m_BGMSound;

	m_BGMSound = nullptr;
}

void c_GameSoundManager::BGMRestart()
{
	if (m_BGMSound == nullptr)return;

	m_BGMSound->Restart(&BGMVolume);
}

void c_GameSoundManager::BGMStop(void)
{
	if (m_BGMSound == nullptr)return;

	m_BGMSound->Stop();
}

void c_GameSoundManager::BGMReset(void)
{
	if (m_BGMSound == nullptr)return;

	m_BGMSound->Reset();
}

bool c_GameSoundManager::JudgData(const S_SOUND_DATA * M_Data, const S_SOUND_DATA * Set_Data)
{
	if (M_Data->Sound_Type != Set_Data->Sound_Type)return false;

	if (M_Data->Sound_CategoryNo != Set_Data->Sound_CategoryNo)return false;

	return true;
}

void c_GameSoundManager::Delete(void)
{
	if (m_SoundManager.size() < 1)return;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		delete m_SoundManager[s];
		m_SoundManager.erase(m_SoundManager.begin() + s);
		s--;
	}
}

void c_GameSoundManager::Delete(unsigned int * count)
{
	m_SoundManager[*count]->Reset();

	delete m_SoundManager[*count];
	m_SoundManager.erase(m_SoundManager.begin() + *count);
	*count--;
}

bool c_GameSoundManager::Delete(const S_SOUND_DATA * M_Data, const bool Flg)
{
	if (m_SoundManager.size() < 1) return true;

	bool L_Flg = true;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (JudgData(M_Data, &m_SoundManager[s]->Get_Data()) == true) {
			if (Flg != true) {
				if (M_Data->Sound_No == m_SoundManager[s]->Get_Data().Sound_No) {
					L_Flg = false;
				}
				else {
					Delete(&s);
				}
			}
			else {
				Delete(&s);
			}
		}
	}

	return L_Flg;
}

bool c_GameSoundManager::SearchNew(const S_SOUND_DATA * Data)
{
	bool PlayFlg = false;

	//サウンドの種類
	switch (Data->Sound_CategoryNo)
	{
	case Co_Sound_Category_Bullet:
		if (Data->Sound_No == 1) {
			m_SoundManager.push_back(new C_Sound_2D_Gun_1());
			PlayFlg = true;
		}
		break;
	case Co_Sound_Category_BGM:
		BGMStart(&Data->Sound_No);
		break;
	case Co_Sound_Category_Warning:
		C_Sound_Warning_Manager WarningManager;
		m_SoundManager.push_back(WarningManager.Get_Warning(&Data->Sound_No));
		PlayFlg = true;
		break;
	case Co_Sound_Category_Click:
		C_Sound_Click_Manager ClickManager;
		m_SoundManager.push_back(ClickManager.Get_Click(&Data->Sound_No));
		PlayFlg = true;
		break;
	case Co_Sound_Category_Explosion:
		C_Sound_Explosion_Manager ExplosionManager;
		m_SoundManager.push_back(ExplosionManager.Get_Sound(Data));
		PlayFlg = true;
		break;
	case Co_Sound_Category_Bullet_Hit:
		break;
	default:
		return false;
		break;
	}

	if (PlayFlg == true) {
		m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &PlayFlg, &SEVolume);
	}

	return true;
}

void c_GameSoundManager::New()
{
	if (Get_Sound_Data_Num() < 1)return;

	for (unsigned int d = 0; d < Get_Sound_Data_Num(); d++) {

		if (Order(&Get_Sound_Data(&d)) == true) {

			Delete_Sound(&d);
		}
	}
}

