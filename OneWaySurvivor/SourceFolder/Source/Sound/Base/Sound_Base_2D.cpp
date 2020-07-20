#include "Sound_Base_2D.h"
#include"../../GameSource/SoundManager.h"

extern SoundManager soundManager;
extern LPDIRECTSOUNDBUFFER lpSPrimary;


extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト

C_Sound_Base_2D::C_Sound_Base_2D()
{
	M_Sound_Data.Sound_Type = Co_Sound_Type_2D;
	M_Init_Flg = true;
	DeleteFlg = 0;

	M_MoveFlg = 0;

	Loop_Mode_Flg = false;
}

C_Sound_Base_2D::~C_Sound_Base_2D()
{
	//StopSound_All();
}

bool C_Sound_Base_2D::Update(const S_CAMERA_POS * CamPos, const bool * PlayFlg, const int * Volume)
{
	if (DeleteFlg > 1)return false;

	soundCol.Sound3D->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
	DWORD SFlg;
	soundCol.Sound->GetStatus(&SFlg);

	if (M_MoveFlg == 2)return true;

	if ((SFlg&DSBSTATUS_PLAYING) != 0) 
	{
		soundCol.Sound->SetVolume(*Volume);
		return true;
	}

	Loop_Mode();

	if ((*PlayFlg != true) && (Loop_Mode_Flg != true)) return true;

	soundCol.Sound->Play(0, 0, 0);
	soundCol.Sound->SetVolume(*Volume);

	M_MoveFlg = 1;


	return true;
}

void C_Sound_Base_2D::Reset(void)
{
	if (soundCol.Sound == nullptr)return;

	DWORD SFlg;
	soundCol.Sound->GetStatus(&SFlg);
	if ((SFlg&DSBSTATUS_PLAYING) != 0) {
		soundCol.Sound->Stop();
		soundCol.Sound->SetCurrentPosition(0);
	}
}

void C_Sound_Base_2D::Stop(void)
{
	soundCol.Sound->Stop();

	M_MoveFlg = 2;
}

void C_Sound_Base_2D::Restart(const int * Volume)
{
	soundCol.Sound->Play(0, 0, 0);
	soundCol.Sound->SetVolume(*Volume);

	M_MoveFlg = 1;
}

void C_Sound_Base_2D::Init_Sound(const int * CategoryNo, const int * No, std::string FileName)
{
	/*if (soundCol != nullptr)return;*/
	if (M_Init_Flg != true)return;
	M_Init_Flg = false;

	M_Sound_Data.Sound_CategoryNo = *CategoryNo;
	M_Sound_Data.Sound_No = *No;

	soundManager.GetSound(&soundCol, FileName);

	Reset();
}

void C_Sound_Base_2D::Loop_Mode(void)
{
	if (Loop_Mode_Flg != false)return;

	DeleteFlg += 1;
}
