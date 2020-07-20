#include "Sound_BGM_Manager.h"
#include"../../GameSource/SoundManager.h"

extern SoundManager soundManager;
extern LPDIRECTSOUNDBUFFER lpSPrimary;


extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト

extern LPDIRECTSOUND3DLISTENER8 lpSListener;

C_Sound_Base_2D * C_Sound_BGM_Manager::Get_BGM(const int * No)
{
	switch (*No)
	{
	case 1:
		return new C_Spund_BGM_Base(1, "../GameFolder/Material/wav/BGM2.wav");
		break;
	case 2:
		return new C_Spund_BGM_Base(2, "../GameFolder/Material/wav/BGM1.wav");
		break;
	case 3:
		return new C_Spund_BGM_Base(3, "../GameFolder/Material/wav/BGM2-2.wav");
		break;
	case 4:
		return new C_Spund_BGM_Base(4, "../GameFolder/Material/wav/BGM_BOSS_1.wav");
		break;
	case 5:
		return new C_Spund_BGM_Base(5, "../GameFolder/Material/wav/BGM_Clear_1.wav");
		break;
	default:
		return new C_Spund_BGM_Base(*No, "../GameFolder/Material/wav/BGM2.wav");
		break;
	}
	return new C_Spund_BGM_Base(*No, "../GameFolder/Material/wav/BGM2.wav");
}
