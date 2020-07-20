#include "StageCar.h"

StageCar::StageCar(const BODYDATA * Data):C_PlayerA(Data)
{
	D3DXMatrixTranslation(&Car.Base.Mat, 0.0f, 0.0f, 0.0f);
	Car.Con.NowSpeed = 0;
}

bool StageCar::Update(void)
{
	//標準パーツのアップデート
	Update_Car_Parts();
	Update_Gun();

	return true;
}
