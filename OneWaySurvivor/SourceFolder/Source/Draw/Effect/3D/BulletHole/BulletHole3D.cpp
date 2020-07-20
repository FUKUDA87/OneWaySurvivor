#include "BulletHole3D.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_BulletHole3D::C_BulletHole3D(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, int TypeNo)
{
	Init();

	Hole.Base.Mat = *Mat;
	Judg judg;
	judg.SetMatP(&Hole.Base.Mat, Pos);

	InitWall(TypeNo);
	InitGround(TypeNo);
}

bool C_BulletHole3D::Update(void)
{
	for (int i = 0; i < 4; i++) {
		Hole.v[i].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	Hole.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	Hole.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	Hole.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	Hole.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	return CountUpdate();
}

void C_BulletHole3D::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	//lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ

	lpD3DDevice->SetTexture(0, Hole.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Hole.Base.Mat);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Hole.v, sizeof(VERTEX));//2はポリゴン数

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void C_BulletHole3D::InitWall(int TypeNo)
{
	if (TypeNo != 1)return;
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.05f, 0.05f);
	Hole.v[0].Pos = D3DXVECTOR3(Pos.x, Pos.y, -Pos.z);
	Hole.v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);
	Hole.v[2].Pos = D3DXVECTOR3(Pos.x, -Pos.y, Pos.z);
	Hole.v[3].Pos = D3DXVECTOR3(Pos.x, -Pos.y, -Pos.z);
}

void C_BulletHole3D::InitGround(int TypeNo)
{
	if (TypeNo != 2)return;
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.05f, 0.0f, 0.05f);
	Hole.v[0].Pos = D3DXVECTOR3(-Pos.x, Pos.y, Pos.z);
	Hole.v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);
	Hole.v[2].Pos = D3DXVECTOR3(Pos.x, Pos.y, -Pos.z);
	Hole.v[3].Pos = D3DXVECTOR3(-Pos.x, Pos.y, -Pos.z);
}

void C_BulletHole3D::Init(void)
{
	//画像のロード
	Hole.Tex = textureManager.GetTexture("BulletBack1C.png", 300, 300, NULL);

	NowCount = 1 * 60;
}

bool C_BulletHole3D::CountUpdate(void)
{
	//一秒減らす
	NowCount -= 1;
	if (NowCount <= 0) {
		//時間が経った
		NowCount = 0;
		return false;
	}
	return true;
}
