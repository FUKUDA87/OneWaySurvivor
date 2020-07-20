#pragma once
#include"../../Base/Sound_Base_2D.h"

class C_Spund_Click_Base :public C_Sound_Base_2D {
public:
	C_Spund_Click_Base(const int No, std::string FileName);

	virtual void Stop_Sound2(void);

	virtual void Start_Sound(void);
};