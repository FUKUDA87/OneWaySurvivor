#include "LaserBase2.h"
#include"../../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

C_LaserBase2::C_LaserBase2(const int * TexNo)
{
	m_LaserTex = { NULL,1,1 };
	m_LaserTex.Tex = textureManager.GetTexture("enemyHp.png", m_LaserTex.Width, m_LaserTex.Height, NULL);
	Init();
}

void C_LaserBase2::SetTexNo(const int * TexNo)
{

}

void C_LaserBase2::GetHitPos(D3DXVECTOR3*StartPos, D3DXVECTOR3*HitPos, const D3DXMATRIX * Mat, const D3DXVECTOR3 * TransPos, const float * Dis)
{
	D3DXMATRIX TmpMat;
	judg.setTransMat(&TmpMat, TransPos);
	TmpMat = TmpMat * (*Mat);
	*StartPos = judg.SetPosM(&TmpMat);

	D3DXVECTOR3 Vec;
	D3DXVec3TransformNormal(&Vec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &TmpMat);
	*HitPos = *StartPos + Vec * (*Dis);
	return;
}

void C_LaserBase2::Init(void)
{
	
}
