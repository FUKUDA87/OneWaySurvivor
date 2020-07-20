#include "PlayerA.h"
#include"../Draw/Gun/Draw/Type/Gun_Gatling_1.h"
#include"../Draw/Effect/Car/Ball/Ball3DVec.h"

C_PlayerA::C_PlayerA()
{
	BodyData.CarBodyNo = CarNo1;
	BodyData.TireNo = TireNo1;
	BodyData.StandNo = StandNo1;
	BodyData.GunNo = 1;
	InitPlayerA();
}

C_PlayerA::C_PlayerA(const BODYDATA * Data)
{
	SetBody(Data);

	//SaveCar();
}

C_PlayerA::~C_PlayerA()
{
}

void C_PlayerA::SetBody(const BODYDATA * Data)
{
	//情報のセット
	BodyData = *Data;
	//パーツのセット
	InitPlayerA();

}

void C_PlayerA::SaveCar(void)
{
	//パーツ情報の読み込み
	int DrawNum;
	C_CarDataManager Manager;
	DrawNum = Manager.GetDrawNum(BodyData.CarBodyNo,true);
	for (int c = 0; c < DrawNum; c++) {
		Manager.GetDrawSet(BodyData.CarBodyNo, &c,true);
	}
}

void C_PlayerA::InitPlayerA(void)
{

	//車初期化
	SetMeshCar(BodyData.CarBodyNo);

	InitBall3D();

	New_Set_Car_Parts(&BodyData);

	
}
