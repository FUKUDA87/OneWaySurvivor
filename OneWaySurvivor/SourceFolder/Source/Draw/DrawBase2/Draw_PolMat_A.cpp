#include "Draw_PolMat_A.h"
#include"../../GameSource/Judgment.h"

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Draw_PolMat_Base_1::C_Draw_PolMat_Base_1(std::string FileName, const S_TEX_POS * Pos):C_Draw_Pol_BASE_A(FileName,Pos)
{
	Draw_JudgFlg = 0;
}

C_Draw_PolMat_Base_1::C_Draw_PolMat_Base_1(std::string FileName, const S_TEX_DRAW_DATA * Data) : C_Draw_Pol_BASE_A(FileName, Data)
{
	Draw_JudgFlg = 0;
}

C_Draw_PolMat_Base_1::~C_Draw_PolMat_Base_1()
{
	Delete_PolMat();
}

void C_Draw_PolMat_Base_1::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Get_MoveVecFlg();

	Draw_PolMat_No1(CameraPos);
}

void C_Draw_PolMat_Base_1::Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (Get_MoveVecFlg() != true)return;

	PolMat_Set_MoveVec(MoveVec);

}

bool C_Draw_PolMat_Base_1::PolMat_Judg(void)
{
	if (M_Polygon.Mat == nullptr)return false;
	if (M_Polygon.Num < 1)return false;

	return true;
}

bool C_Draw_PolMat_Base_1::PolMat_Judg(const int PolNum)
{
	int Num = PolNum;
	if (Num < 1)Num = 1;

	if (M_Polygon.Mat == nullptr)return false;
	if (M_Polygon.Num < Num)return false;

	return true;
}

void C_Draw_PolMat_Base_1::Init_PolMat(const int PolNum)
{
	//Delete_PolMat();

	int Num = PolNum;
	if (Num < 1)Num = 1;
	M_Polygon.Num = Num;

	M_Polygon.Mat = new D3DXMATRIX[M_Polygon.Num];
}

void C_Draw_PolMat_Base_1::Delete_PolMat(void)
{
	if (M_Polygon.Mat == nullptr)return;

	delete[] M_Polygon.Mat;
}

void C_Draw_PolMat_Base_1::Init_PolMat_Mat(const D3DXMATRIX * Mat)
{
	//if (PolMat_Judg() != true)return;

	for (int p = 0; p < M_Polygon.Num; p++) {
		M_Polygon.Mat[p] = *Mat;
	}
}

void C_Draw_PolMat_Base_1::Set_PolMat_Mat(const D3DXMATRIX * Mat)
{
	if (PolMat_Judg(2) != true)return;

	for (int p = Get_PolMatNum() - 1;p>0; p--) {
		M_Polygon.Mat[p] = M_Polygon.Mat[p - 1];
	}

	M_Polygon.Mat[0] = *Mat;
}

void C_Draw_PolMat_Base_1::PolMat_Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (PolMat_Judg() != true)return;

	Judg judg;

	for (int p = 0; p < Get_PolMatNum(); p++) {
		judg.VecMatIn(&M_Polygon.Mat[p], MoveVec);
	}
}

void C_Draw_PolMat_Base_1::Draw_PolMat_No1(const D3DXVECTOR3 * CameraPos)
{
	if (PolMat_Judg(2) != true)return;

	Judg judg;
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	
	int c = 255;
	Pol_SetAllColor(&c);

	lpD3DDevice->SetTexture(0, M_Tex.Tex);
	
	lpD3DDevice->SetTransform(D3DTS_WORLD, &Get_IdenMat());

	for (int i = 0; i < (Get_PolMatNum() - 1); i++) {
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		judg.SetPosM(&nPos, &M_Polygon.Mat[i]);
		judg.SetPosM(&oPos, &M_Polygon.Mat[i + 1]);
		float L_Size = Get_ScalPos().x;
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &L_Size);


		v[0].Pos = nPos - vec;
		v[1].Pos = nPos + vec;
		v[2].Pos = oPos + vec;
		v[3].Pos = oPos - vec;
		v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(Get_PolMatNum() - 1));
		v[1].Tex = D3DXVECTOR2(1.0f, (float)i / (float)(Get_PolMatNum() - 1));
		v[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (float)(Get_PolMatNum() - 1));
		v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(Get_PolMatNum() - 1));

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2はポリゴン数
	}

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
