#include "Draw_Pol_A.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../GameSource/Judgment.h"

extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

extern LPDIRECT3DDEVICE9 lpD3DDevice;

C_Draw_Pol_BASE_A::C_Draw_Pol_BASE_A()
{
	Init_Pol();
}

C_Draw_Pol_BASE_A::C_Draw_Pol_BASE_A(const D3DXVECTOR3 * Pos_A, const D3DXVECTOR3 * Pos_B, const D3DXVECTOR3 * Pos_C, const D3DXVECTOR3 * Pos_D)
{
	v_Pos[0] = *Pos_A;
	v_Pos[1] = *Pos_B;
	v_Pos[2] = *Pos_C;
	v_Pos[3] = *Pos_D;
	Pol_SetPos(&v_Pos[0], &v_Pos[1], &v_Pos[2], &v_Pos[3]);
	int alpha = 255;
	Pol_SetAllColor(&alpha);

	Init_Pol();
}

C_Draw_Pol_BASE_A::C_Draw_Pol_BASE_A(std::string FileName, const S_TEX_POS * Pos)
{
	Texture_Load(FileName, Pos);
	Init_Pol();
}

C_Draw_Pol_BASE_A::C_Draw_Pol_BASE_A(std::string FileName, const S_TEX_DRAW_DATA * Data)
{
	Texture_Load(FileName, Data);
	Init_Pol();
}

void C_Draw_Pol_BASE_A::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Get_MoveVecFlg();

	Draw_Pol_No1();
}

void C_Draw_Pol_BASE_A::Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (Get_MoveVecFlg() != true)return;

	
}

LPD3DXMESH C_Draw_Pol_BASE_A::Get_Mesh(void)
{
	return LPD3DXMESH();
}

D3DXVECTOR3 C_Draw_Pol_BASE_A::Get_Pol_Pos(const int * PosNo)
{
	return v[*PosNo].Pos;
}

D3DXMATRIX C_Draw_Pol_BASE_A::Get_DrawMat(void)
{
	return M_Mat;
}

///////////////////////////////////////////////////////////////////////////////

void C_Draw_Pol_BASE_A::Texture_Load(std::string FileName, const S_TEX_POS * Pos)
{
	M_Tex = { NULL,Pos->Width,Pos->Height };
	M_Tex.Tex=textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, NULL);
}

void C_Draw_Pol_BASE_A::Texture_Load(std::string FileName, const S_TEX_DRAW_DATA * Data)
{
	M_Tex = { NULL,Data->Pos.Width,Data->Pos.Height };
	M_Tex.Tex = textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, D3DCOLOR_XRGB(Data->Color.r, Data->Color.g, Data->Color.b));
}

void C_Draw_Pol_BASE_A::Pol_SetPos(const D3DXVECTOR3 * v_A, const D3DXVECTOR3 * v_B, const D3DXVECTOR3 * v_C, const D3DXVECTOR3 * v_D)
{
	v[0].Pos = *v_A;
	v[1].Pos = *v_B;
	v[2].Pos = *v_C;
	v[3].Pos = *v_D;
}

void C_Draw_Pol_BASE_A::Pol_SetAllColor(const int * Alpha)
{
	for (int p = 0; p < 4; p++) {
		v[p].Color = D3DCOLOR_ARGB(*Alpha, 255, 255, 255);
	}
}

void C_Draw_Pol_BASE_A::Pol_SetAllTex(const D3DXVECTOR2 * t_A, const D3DXVECTOR2 * t_B, const D3DXVECTOR2 * t_C, const D3DXVECTOR2 * t_D)
{
	v[0].Tex = *t_A;
	v[1].Tex = *t_B;
	v[2].Tex = *t_C;
	v[3].Tex = *t_D;
}

void C_Draw_Pol_BASE_A::Init_Pol(void)
{
	Draw_JudgFlg = Co_Draw_Pol;
}

void C_Draw_Pol_BASE_A::Draw_Pol_No1(void)
{
	Judg judg;
	D3DXVECTOR3 PosA = judg.GetVecVec(&v_Pos[0], &Get_ScalPos());
	D3DXVECTOR3 PosB = judg.GetVecVec(&v_Pos[1], &Get_ScalPos());
	D3DXVECTOR3 PosC = judg.GetVecVec(&v_Pos[2], &Get_ScalPos());
	D3DXVECTOR3 PosD = judg.GetVecVec(&v_Pos[3], &Get_ScalPos());
	Pol_SetPos(&PosA, &PosB, &PosC, &PosD);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, NULL);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Get_Mat());
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void C_Draw_Pol_BASE_A::Draw_Pol_No2(void)
{
	/*Judg judg;
	D3DXVECTOR3 PosA = judg.GetVecVec(&v_Pos[0], &Get_ScalPos());
	D3DXVECTOR3 PosB = judg.GetVecVec(&v_Pos[1], &Get_ScalPos());
	D3DXVECTOR3 PosC = judg.GetVecVec(&v_Pos[2], &Get_ScalPos());
	D3DXVECTOR3 PosD = judg.GetVecVec(&v_Pos[3], &Get_ScalPos());
	Pol_SetPos(&PosA, &PosB, &PosC, &PosD);*/

	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, M_Tex.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Get_Mat());
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}


