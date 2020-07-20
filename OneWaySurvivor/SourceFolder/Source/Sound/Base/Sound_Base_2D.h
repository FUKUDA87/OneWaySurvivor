#pragma once
#include<d3dx9.h>
#include<dsound.h>
#include"../../GameSource/Struct.h"
#include"../../Const/Const_Sound_Type.h"
#include<string>


class C_Sound_Base_2D {
public:
	C_Sound_Base_2D();
	~C_Sound_Base_2D();

	// 更新処理
	virtual bool Update(const S_CAMERA_POS* CamPos, const bool *PlayFlg,const int *Volume);

	// 曲を最初に戻す
	void Reset(void);

	// 中断
	virtual void Stop(void);

	// 再開
	virtual void Restart(const int *Volume);

	S_SOUND_DATA Get_Data(void) {
		return M_Sound_Data;
	}
protected:
	//今のサウンド
	int NowSound;
	//サウンド変数
	SoundCol soundCol;

	//サウンド番号
	S_SOUND_DATA M_Sound_Data;

	//初期化
	void Init_Sound(const int *CategoryNo,const int *No, std::string FileName);

	int M_MoveFlg;

	//音をループさせる処理
	void Loop_Mode(void);

	bool Loop_Mode_Flg;

	bool M_Init_Flg;

	int DeleteFlg;
private:
	
};