#pragma once
#include"Departure_Gun_Auto_Base.h"

//発射する弾数の制限処理と発射回数処理
class C_Departure_A :public C_Departure_Gun_Auto_Base {
public:
	C_Departure_A(const int *Count);
protected:
	//今のカウントの変更処理
	virtual void Update_NowCount(const int *Count);
};