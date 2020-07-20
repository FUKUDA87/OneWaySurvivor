#pragma once
#include<d3dx9.h>

class C_CountBase
{
public:
	C_CountBase(const int StartNum);

	// 更新処理(カウント終了するとfalse)
	bool Update(void);

	// 今のカウント入れ
	void setNowCount(const int NewCount) { nowCount = NewCount; }

	// 今のカウント渡し
	int getNowCount(void) { return nowCount; }
private:
	int nowCount;
};