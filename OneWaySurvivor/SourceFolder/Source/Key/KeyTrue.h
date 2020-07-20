#pragma once
#include"Key.h"

class C_KeyTrue :public Key {
public:
	//右クリック
	bool RClick();
	//左クリック
	bool LClick();
	//左クリック+KeyFlg
	bool LClickF();
	//左クリック+KeyFlg
	bool LClickF_N();
private:
	static bool LClickFlg;
};