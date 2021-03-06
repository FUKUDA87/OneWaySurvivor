#pragma once
#include"Gun_Trigger_Base.h"

//ひとつの銃口発射
class C_Gun_Trigger_2 :public C_Gun_Trigger_Base {
public:
	C_Gun_Trigger_2();
	//銃口のトリガーをオンにする処理
	void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg);
	//銃口のチェンジ
	void Gun_Mouth_Change(void);
protected:
	//初期化
	void Init(void);

	//銃口No
	unsigned int MouthNo;
};