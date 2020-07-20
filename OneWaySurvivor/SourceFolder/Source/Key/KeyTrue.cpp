#include "KeyTrue.h"

bool C_KeyTrue::LClickFlg = false;

bool C_KeyTrue::RClick()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		return true;
	}
	
	return false;
}

bool C_KeyTrue::LClick()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		return true;
	}
	return false;
}

bool C_KeyTrue::LClickF()
{
	if (LClick() == true) {
		if (LClickFlg == false) {
			LClickFlg = true;
			return true;
		}
	}
	else {
		LClickFlg = false;
	}
	return false;
}

bool C_KeyTrue::LClickF_N()
{
	if (LClick() == true) {
		if (LClickFlg == false) {
			return true;
		}
	}
	else {
		LClickFlg = false;
	}
	return false;
}
