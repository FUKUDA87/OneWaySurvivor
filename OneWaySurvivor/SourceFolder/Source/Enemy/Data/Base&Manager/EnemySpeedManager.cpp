#include "EnemySpeedManager.h"

C_Speed_Update * C_EnemySpeedManager::GetEnemySpeed(const int * EnemyNo)
{
	switch (*EnemyNo)
	{
	case EnemyNo1:
		return new SpeedUp1();
		break;
	case EnemyBossNo101:
		return new C_Enemy101_Speed_1();
		break;
	default://ŒŸõ‚Éˆø‚Á‚©‚©‚ç‚È‚¢
		return new SpeedUp1();
		break;
	}

	//ŒŸõ‚Éˆø‚Á‚©‚©‚ç‚È‚¢
	return new SpeedUp1();
}
