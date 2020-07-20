#include "Stand_No0.h"
#include"../../Move/Parts/StopMove.h"

C_Stand_No0::C_Stand_No0(const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move):C_Car_Parts_Joint(Data)
{
	New_Move(Move);
}
