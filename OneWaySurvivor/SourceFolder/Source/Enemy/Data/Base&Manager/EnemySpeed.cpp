#include "EnemySpeed.h"

bool C_Speed_Update::CountUpdate(void)
{
	if (CountDownNow <= 0) {
		CountDownNow = CountDown;
	}
	CountDownNow -= 1;
	if (CountDownNow <= 0)return false;
	return true;
}
