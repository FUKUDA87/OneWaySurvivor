#pragma once
#include"Gun_Trigger_Base.h"

//全銃口発射
class C_Gun_Trigger_1:public C_Gun_Trigger_Base {
public:
	//銃口のトリガーをオンにする処理
	void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg);
	//銃口のチェンジ
	void Gun_Mouth_Change(void);
protected:

};