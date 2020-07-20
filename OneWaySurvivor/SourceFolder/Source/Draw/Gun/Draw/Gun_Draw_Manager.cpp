#include "Gun_Draw_Manager.h"
#include"Type/Gun_Gatling_1.h"
#include"Move/GunStopMove_1.h"
#include"Type/Gun_No201.h"
#include"Type/Gun_No101.h"

C_GunLaser * C_Gun_Darw_Manager::Get_Gun(const int *GunNo,C_GunMoveBase_A * Move)
{
	if (*GunNo == 1)return new C_Gun_Gatling(Move);
	if (*GunNo == 101)return new C_Gun_No101(Move);
	if (*GunNo == 201)return new C_Gun_No201(Move);
	return new C_Gun_Gatling(Move);
}

C_GunLaser * C_Gun_Darw_Manager::Get_Gun_Stop(const int * GunNo)
{
	return Get_Gun(GunNo,new C_GunStopMove_1());
}
