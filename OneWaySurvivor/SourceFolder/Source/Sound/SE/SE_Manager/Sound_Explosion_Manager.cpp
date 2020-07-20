#include "Sound_Explosion_Manager.h"

C_Sound_Base_3D * C_Sound_Explosion_Manager::Get_Sound(const S_SOUND_DATA * Data)
{
	switch (Data->Sound_No)
	{
	case 1:
		return new C_Sound_Base_3D(Data, "../GameFolder/Material/wav/bomb1.wav");
		break;
	default:
		return new C_Sound_Base_3D(Data, "../GameFolder/Material/wav/bomb1.wav");
		break;
	}
	return new C_Sound_Base_3D(Data, "../GameFolder/Material/wav/bomb1.wav");
}
