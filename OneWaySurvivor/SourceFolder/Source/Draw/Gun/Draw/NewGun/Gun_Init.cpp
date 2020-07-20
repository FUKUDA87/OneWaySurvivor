#include "Gun_Init.h"

S_Gun_Parts_Data C_Gun_Init::Get_Data_Set(const bool BulletFlg, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * MouthPos, const int Rate, const int BulletNo, const int CategoryNo)
{
	S_Gun_Parts_Data Data;
	Data.BulletFlg = BulletFlg;
	Data.TarnsPos = *TransPos;
	Data.Rate = Rate;
	Data.BulletNo = BulletNo;
	Data.MouthPos = *MouthPos;
	Data.CategoryNo = CategoryNo;
	return Data;
}
