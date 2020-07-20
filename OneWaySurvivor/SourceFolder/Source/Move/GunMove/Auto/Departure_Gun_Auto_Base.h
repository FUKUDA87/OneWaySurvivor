#pragma once
#include<d3dx9.h>

class C_Departure_Gun_Auto_Base {
public:
	C_Departure_Gun_Auto_Base(const int *Count);
	//弾を撃つことができるFlg渡し
	bool Get_BulletFlg(const int *Count);
protected:
	int NowCount;

	//今のカウントの変更処理
	virtual void Update_NowCount(const int *Count);
};