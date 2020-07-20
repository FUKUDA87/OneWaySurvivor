#include "Count.h"
#include"../Judgment.h"

C_Count::C_Count(const int * Start)
{
	//‰Šú‰»
	CountStart = *Start;

	StartFlg = true;

}

bool C_Count::Update(void)
{
	SetNow();

	CountDownNow--;

	if (CountDownNow <= 0)StartFlg = true;

	return StartFlg;
}

bool C_Count::Update_Count(void)
{
	SetNow();

	CountDownNow--;

	if (CountDownNow <= 0)StartFlg = true;

	Judg judg;
	return judg.ReverseFlg2(&StartFlg);
}

void C_Count::UpCount(void)
{
	CountDownNow++;
}

void C_Count::SetNow(void)
{
	if (StartFlg != true)return;

	CountDownNow = CountStart;

	StartFlg = false;
}