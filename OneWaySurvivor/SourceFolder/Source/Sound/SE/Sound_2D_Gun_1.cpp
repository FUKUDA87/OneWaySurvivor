#include "Sound_2D_Gun_1.h"
#include"../../GameSource/SoundManager.h"

extern SoundManager soundManager;
extern LPDIRECTSOUNDBUFFER lpSPrimary;


extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト

extern LPDIRECTSOUND3DLISTENER8 lpSListener;

C_Sound_2D_Gun_1::C_Sound_2D_Gun_1()
{
	int i = 1;
	Init_Sound(&Co_Sound_Category_Bullet, &i, "../GameFolder/Material/wav/Gun4.wav");
}
