#include "Sound_Click_Manager.h"

C_Sound_Base_2D * C_Sound_Click_Manager::Get_Click(const int * No)
{
	switch (*No)
	{
	case 1:
		return new C_Spund_Click_Base(1, "../GameFolder/Material/wav/decision18.wav");
		break;
	default:
		return new C_Spund_Click_Base(1, "../GameFolder/Material/wav/decision18.wav");
		break;
	}
	return new C_Spund_Click_Base(1, "../GameFolder/Material/wav/decision18.wav");
}
