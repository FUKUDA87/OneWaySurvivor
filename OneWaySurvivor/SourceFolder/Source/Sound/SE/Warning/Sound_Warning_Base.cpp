#include "Sound_Warning_Base.h"

C_Spund_Warning_Base::C_Spund_Warning_Base(const int No, std::string FileName)
{
	Loop_Mode_Flg = true;

	Init_Sound(&Co_Sound_Category_Warning, &No, FileName);
}
