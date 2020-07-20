#include "PartsTrans.h"

StateMove * C_TireMove::Action(ObjectParts *ObjPar)
{
	ObjPar->Base.Mat = ObjPar->Base.RotX*ObjPar->Base.RotY*ObjPar->Base.Trans*ObjPar->SuperMat;
	return nullptr;
}
