#include "Smoke.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"
#include"../../../../Car/Data/Draw3DManager/CarSmogManager.h"

extern LPDIRECT3DDEVICE9	lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

c_Smoke::c_Smoke(const int * CarNo, const D3DXMATRIX * Mat, const float * HpPer, const int * NowHp)
{
	C_CarSmogManager L_CarSmogManager;
	smoke = L_CarSmogManager.GetSmog(CarNo);

	//ŽžŒÀ‚Ì‰Šú‰»
	count = new C_CountBase(smoke.AStart);

	smokePol.Tex = textureManager.GetTexture("Smoke.png", 256, 256, NULL);

	// ‰Œ‚Ì”Z‚³‚Ì‰Šú‰»
	Draw_No = InitDrawNo(HpPer, NowHp);

	smokePol.Base.Mat = L_CarSmogManager.GetPos(CarNo) * (*Mat);

	//ˆÚ“®ƒxƒNƒgƒ‹‚Ì‰Šú‰»
	Judg judg;
	smokePol.Base.TraPos = smoke.MoveVec;

	//ˆÚ“®‚Å•ªŽU‚³‚¹‚é
	D3DXVECTOR3 L_RandPos = D3DXVECTOR3(RandPlus(&smoke.Random.x), RandPlus(&smoke.Random.y), RandPlus(&smoke.Random.z));
	smokePol.Base.TraPos += judg.GetVecVec_S(&L_RandPos, &smoke.Frame);

	smokePol.Base.TraPos *= 0.5f;

}

c_Smoke::~c_Smoke()
{
	if (count != nullptr)delete count;
}

bool c_Smoke::Update(const s_CarEffectUpdateData * updateData)
{
	//ˆÚ“®
	Judg judg;
	judg.setTransMat(&smokePol.Base.Trans, &smokePol.Base.TraPos);
	smokePol.Base.Mat = smokePol.Base.Trans*smokePol.Base.Mat;

	judg.VecMatIn(&smokePol.Base.Mat, &updateData->MoveVec);
	
	Update_Alpha();

	return count->Update();
}

void c_Smoke::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO

	for (int v = 0; v < 4; v++) {
		smokePol.v[v].Color = D3DCOLOR_ARGB(smoke.Alpha, 255, 255, 255);
	}
	lpD3DDevice->SetTexture(0, smokePol.Tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

	Judg judg;
	judg.SetPosM(&smokePol.Base.Pos, &smokePol.Base.Mat);

	//ƒrƒ‹ƒ{[ƒh
	D3DXVECTOR3 vec, oPos, nPos;
	vec = D3DXVECTOR3(0.0f, GetPolSize(), 0.0f);
	nPos = smokePol.Base.Pos + vec;
	oPos = smokePol.Base.Pos - vec;
	vec = judg.Billboard(&oPos, &nPos, CameraPos, &vec.y);
	smokePol.v[0].Pos = nPos - vec;
	smokePol.v[1].Pos = nPos + vec;
	smokePol.v[2].Pos = oPos + vec;
	smokePol.v[3].Pos = oPos - vec;
	int num = Draw_No;
	smokePol.v[0].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8) / 256.0f);
	smokePol.v[1].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8) / 256.0f);
	smokePol.v[2].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	smokePol.v[3].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smokePol.v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

int c_Smoke::InitDrawNo(const float * HpPer, const int * NowHp)
{
	if (*NowHp <= 0)return 35;
	if (*HpPer < 0.1f)return 47;
	if (*HpPer < 0.2f)return 50;
	if (*HpPer < 0.3f)return 53;
	
	return 0;

	//”–‚¢‚S‚VA”Z‚¢‚R‚T
	//”Z‚¢47,”–‚¢53
}

void c_Smoke::Update_Alpha(void)
{
	if (count->getNowCount() < smoke.AStart) smoke.Alpha -= smoke.ADown;
	if (smoke.Alpha <= 0)
	{
		smoke.Alpha = 0;
		count->setNowCount(0);
	}
}

float c_Smoke::RandPlus(const int * Num)
{
	if (*Num <= 0)return 0.0f;

	int x = rand() % (*Num);
	if (rand() % 2 < 1)x *= -1;
	return (float)x;
}

float c_Smoke::GetPolSize(void)
{
	smoke.PolBit += smoke.PolBitUp;
	if (smoke.PolBit > 1.0f)smoke.PolBit = 1.0f;
	float f = smoke.PolSize*smoke.PolBit;
	return f;
}