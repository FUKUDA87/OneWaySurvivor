#include "Gun_No101.h"
#include"../../../DrawBase2/Draw_Mesh_Base_A.h"
#include"../Trigger/Gun_Trigger_1.h"

C_Gun_No101::C_Gun_No101(C_GunMoveBase_A * Move)
{
	//銃の情報の初期化
	M_S_GunData.Depar.Bullet_Gun_Mode = 1;
	M_S_GunData.Depar.Count_Departure = 1;
	//中心の行列の動きの初期化
	New_GunMove(Move);
	//パーツの初期化
	M_GunParts.push_back(new C_PartsDraw_Gun(new C_Draw_Mesh_Base("gun2EC.x")
		, &Get_Data_Set(true, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.8f), 180, 1, 0)));
	//カテゴリーの初期化
	int i = 0;
	M_Category_Data.push_back(new C_Gun_Parts_Category(&i));
	//引き金の初期化
	M_C_Trigger = new C_Gun_Trigger_1();

	BulletShotEffectNum = 0;
}
