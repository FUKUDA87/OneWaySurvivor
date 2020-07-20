#pragma once
#include"Type/Gun_Gatling_1.h"

class C_Gun_Darw_Manager {
public:
	C_GunLaser* Get_Gun(const int *GunNo,C_GunMoveBase_A *Move);
	C_GunLaser* Get_Gun_Stop(const int *GunNo);
};