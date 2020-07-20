#include "LaserManager.h"

void LaserManager::LaserCha(LaserBase * NewLaser)
{
	if (laserBase != nullptr) {
		delete laserBase;
	}
	laserBase = NewLaser;
}

bool LaserManager::UpdateS(D3DXMATRIX Mat, D3DXMATRIX Tmp)
{
	laserBase->UpdateS(Mat, Tmp);
	return true;
}

bool LaserManager::UpdateL(float Dis, bool Flg)
{
	laserBase->UpdateL(Dis, Flg);
	return true;
}
