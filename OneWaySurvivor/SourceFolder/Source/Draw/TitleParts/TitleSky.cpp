#include "TitleSky.h"
#include"../../MaterialManager/XfileManager.h"

extern XFileManager xfileManager;

StageSky::StageSky()
{
	sky.Mesh=xfileManager.GetMesh("garezi1.x");
	D3DXVECTOR3 Pos(4, 3, 4);
	D3DXMatrixScaling(&sky.Base.Scal, Pos.x, Pos.y, Pos.z);
}
