#include "Sound_2D_Bullet_Hit.h"

C_Spund_2D_Bullet_Hit_Base::C_Spund_2D_Bullet_Hit_Base(const S_SOUND_DATA * Data, std::string FileName)
{
	Init_Sound(&Data->Sound_CategoryNo, &Data->Sound_No, FileName);
}
