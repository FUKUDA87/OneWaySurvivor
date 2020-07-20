#pragma once
#include"Departure_Gun_Auto_Base.h"

//発射時間の処理
class C_Departure_B :public C_Departure_Gun_Auto_Base {
public:
	C_Departure_B(const int *Count);
private:
	//今のカウントの変更処理
	virtual void Update_NowCount(const int *Count) {
		NowCount--;
	}

};