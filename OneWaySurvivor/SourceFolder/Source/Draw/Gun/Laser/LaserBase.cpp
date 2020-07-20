#include "LaserBase.h"

LaserBase::LaserBase()
{
	lasFlg = false; 
	LasDis = 0.0f;
}

LaserBase::LaserBase(float Dis)
{
	lasFlg = false; 
	LasDis = Dis;
}
