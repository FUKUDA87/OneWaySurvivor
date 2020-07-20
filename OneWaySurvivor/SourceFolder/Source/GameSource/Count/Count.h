#pragma once
#include<d3dx9.h>

class C_Count
{
public:
	C_Count(const int *Start);
	//カウントダウン(0になればtrue)
	bool Update(void);
	//カウントダウン(0になればfalse)
	bool Update_Count(void);
	//間隔の調整用
	void UpCount(void);

private:
	//今減る数
	int CountDownNow;
	//始まりの数
	int CountStart;
	//切り替えFlg
	bool StartFlg;
	//代入
	void SetNow(void);
};