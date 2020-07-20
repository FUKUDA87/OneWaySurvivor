#include "Sound_BGM_Base.h"

C_Spund_BGM_Base::C_Spund_BGM_Base(const int  No, std::string FileName)
{
	Loop_Mode_Flg = true;

	Init_Sound(&Co_Sound_Category_BGM, &No, FileName);
}
