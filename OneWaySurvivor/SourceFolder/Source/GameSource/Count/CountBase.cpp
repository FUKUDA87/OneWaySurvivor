#include "CountBase.h"

C_CountBase::C_CountBase(const int StartNum)
{
	nowCount = StartNum;
}

bool C_CountBase::Update(void)
{
	nowCount--;

	if (nowCount <= 0) 
	{
		nowCount = 0;
		return false;
	}

	return true;
}
