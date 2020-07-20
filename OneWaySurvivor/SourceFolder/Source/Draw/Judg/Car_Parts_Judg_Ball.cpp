#include "Car_Parts_Judg_Ball.h"
#include"../../Move/Parts/StopMove.h"
#include"../DrawBase2/Draw_Ball_A.h"

C_Car_Parts_Judg_Ball::C_Car_Parts_Judg_Ball(const S_CAR_PARTS_DATA * Data, const float Dis):C_Car_Parts_Joint(Data)
{
	New_Move(new C_StopMove());
	Draw_New(new C_Draw_Ball_A(Dis));
	Draw_Flg = false;
}
