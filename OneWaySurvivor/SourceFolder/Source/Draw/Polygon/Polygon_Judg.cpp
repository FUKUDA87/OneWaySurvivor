#include "Polygon_Judg.h"
#include"../../Move/Parts/StopMove.h"
#include"../DrawBase2/Draw_Pol_A.h"

C_Car_Parts_Judg_Polygon::C_Car_Parts_Judg_Polygon(const S_CAR_PARTS_DATA * Data,
	const D3DXVECTOR3 * Pos_A, const D3DXVECTOR3 * Pos_B, const D3DXVECTOR3 * Pos_C, const D3DXVECTOR3 * Pos_D):C_Car_Parts_Joint(Data)
{
	New_Move(new C_StopMove());
	Draw_New(new C_Draw_Pol_BASE_A(
		Pos_A, Pos_B, Pos_C, Pos_D));
	Draw_Flg = false;
}

