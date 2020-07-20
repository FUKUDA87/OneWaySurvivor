#include "PolygonBase.h"

void C_PolygonBase::Pol_SetPos(const D3DXVECTOR3 * v_A, const D3DXVECTOR3 * v_B, const D3DXVECTOR3 * v_C, const D3DXVECTOR3 * v_D)
{
	v[0].Pos = *v_A;
	v[1].Pos = *v_B;
	v[2].Pos = *v_C;
	v[3].Pos = *v_D;
}

void C_PolygonBase::Pol_SetAllColor(const int * Alpha)
{
	for (int p = 0; p < 4; p++) {
		v[p].Color = D3DCOLOR_ARGB(*Alpha, 255, 255, 255);
	}
}

void C_PolygonBase::Pol_SetAllTex(const D3DXVECTOR2 * t_A, const D3DXVECTOR2 * t_B, const D3DXVECTOR2 * t_C, const D3DXVECTOR2 * t_D)
{
	v[0].Tex = *t_A;
	v[1].Tex = *t_B;
	v[2].Tex = *t_C;
	v[3].Tex = *t_D;
}
