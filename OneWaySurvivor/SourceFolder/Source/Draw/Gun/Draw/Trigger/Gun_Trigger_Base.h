#pragma once
#include<d3dx9.h>
#include"../Parts/Gun_Parts_Category.h"
#include<vector>

class C_Gun_Trigger_Base {
public:
	//銃口のトリガーをオンにする処理
	virtual void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg) = 0;
	//銃口のチェンジ
	virtual void Gun_Mouth_Change(void) = 0;
};