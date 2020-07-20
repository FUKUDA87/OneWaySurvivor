#pragma once
#include"Gun_Trigger_Base.h"

//‚Ğ‚Æ‚Â‚ÌeŒû”­Ë
class C_Gun_Trigger_2 :public C_Gun_Trigger_Base {
public:
	C_Gun_Trigger_2();
	//eŒû‚ÌƒgƒŠƒK[‚ğƒIƒ“‚É‚·‚éˆ—
	void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg);
	//eŒû‚Ìƒ`ƒFƒ“ƒW
	void Gun_Mouth_Change(void);
protected:
	//‰Šú‰»
	void Init(void);

	//eŒûNo
	unsigned int MouthNo;
};