#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../Const/Const_Sound_Type.h"
#include"Base/Sound_Base_2D.h"
#include"vector/Sound_Data_Vector.h"
#include"../Const/Const_Damage.h"
#include<vector>

//サウンドの流すクラス
class c_GameSoundManager:public C_Sound_Data_Vector {
public:
	c_GameSoundManager(const int *g_BGMVolume, const int *g_SEVolume);
	~c_GameSoundManager();

	//音の更新
	bool Update(void);
	bool Update(const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead);
	void UpdateVolume(const int *g_BGMVolume, const int *g_SEVolume);

	// 音声変更
	bool Order(const S_SOUND_DATA* M_Data);

	// 新規再生
	void New(void);// DataVectorのNew

	// サウンドの初期化
	void Reset(void);

	// サウンドの停止
	void Stop(void);
	void Stop(const S_SOUND_DATA * M_Data);

	// 停止しているサウンドの再生
	void Restart(void);
	void Restart(const S_SOUND_DATA * M_Data);

	//被弾音を流す処理
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos);

	//被弾した物体が無敵状態の判定と音を流す処理
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos,const bool *DamageFlg);

	/*BGM*/

	// 再生開始
	void BGMStart(const int *No);
	// 削除
	void BGMDelete(void);
	// 再生再開
	void BGMRestart(void);
	// 停止
	void BGMStop(void);
	// 初期化
	void BGMReset(void);

private:
	std::vector<C_Sound_Base_2D*>m_SoundManager;
	C_Sound_Base_2D *m_BGMSound;

	S_CAMERA_POS M_CamPos;

	//情報の検索
	bool JudgData(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);

	// 全削除
	void Delete(void);
	void Delete(unsigned int *count);  // 1つだけ削除
	bool Delete(const S_SOUND_DATA* M_Data, const bool Flg);// 削除

	//音を外部からNew
	bool SearchNew(const S_SOUND_DATA* Data);

	int BGMVolume, SEVolume;
};