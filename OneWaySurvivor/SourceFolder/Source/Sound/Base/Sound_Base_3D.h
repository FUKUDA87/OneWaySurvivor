#pragma once
#include"Sound_Base_2D.h"

class C_Sound_Base_3D :public C_Sound_Base_2D {
public:
	C_Sound_Base_3D(const S_SOUND_DATA *Data, std::string FileName);
	bool Update(const S_CAMERA_POS* CamPos, const bool *Flg, const int *Volume);
};