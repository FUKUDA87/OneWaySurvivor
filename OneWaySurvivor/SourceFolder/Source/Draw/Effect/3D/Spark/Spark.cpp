#include "Spark.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


C_Spark::C_Spark(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos)
{
	Init();
	//角度の初期化
	spark.Base.Mat = *Mat;
	//X軸の回転角度を求める
	int Big = 3500,Small=-6000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small)/100.0f;
	//X回転と移動行列
	D3DXMATRIX Rot,Trans;
	//回転
	D3DXMatrixRotationX(&Rot, D3DXToRadian(Ang));
	//ずらす
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, 0.15f);
	//位置の初期化
	Judg judg;
	judg.SetMatP(&spark.Base.Mat, Pos);
	spark.Base.Mat = Rot * Trans * spark.Base.Mat;
	//他の行列を初期化
	for (int p = 0; p < PNum; p++) {
		spark.m.Mat[p] = spark.Base.Mat;
	}
}

C_Spark::~C_Spark()
{
	//ポリゴン表示用の削除
	if (spark.m.Mat != nullptr) {
		delete[] spark.m.Mat;
	}
}

void C_Spark::Init()
{
	//移動量Flg//ポリゴン数の初期化
	PNum = 3;
	//ポリゴン表示用のMatの初期化
	spark.m.Mat = new D3DXMATRIX[PNum];
	CarMoveFlg = false;
	//画像のロード
	//ポリゴンサイズの初期化
	PolSize = 0.015f;
	char TexName[100];
	sprintf_s(TexName, sizeof(TexName), "spark10-1.png");
	spark.Tex = textureManager.GetTexture(TexName, 300, 300, NULL);
	//移動行列の初期化
	D3DXMatrixTranslation(&spark.Base.Mat, 0.0f, 0.0f, 0.0f);
	
	for (int p = 0; p < PNum; p++) {
		spark.m.Mat[p] = spark.Base.Mat;
	}

	//表示の行列
	D3DXMatrixIdentity(&IdenMat);

	//移動処理の初期化
	yUp = 0.25f;
	yDown = -0.1f;
	zDown = -0.35f;

	//時限の初期化
	NowCount = 1 * 60;

}

bool C_Spark::Update(void)
{
	return UpdateSpark();
}

bool C_Spark::UpdateSpark(void)
{
	//上移動と後ろ移動
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
	spark.Base.Mat = Tmp * spark.Base.Mat;
	spark.Base.Mat._42 += yUp;
	//ジャンプ処理
	if (yUp > 0.0f) {
		yUp += yDown;
	}
	else {
		yUp += yDown * 0.5f;
	}
	//行列の更新
	for (int i = (PNum - 1); i > 0; i--) {
		spark.m.Mat[i] = spark.m.Mat[i - 1];
	}
	//先頭に一番新しい行列の代入
	spark.m.Mat[0] = spark.Base.Mat;
	return CountUpdate();
}

bool C_Spark::Update(const D3DXVECTOR3 * CarMoveVec)
{
	////移動量を入れていいのかの計算
	//if (CarMoveFlg == true) {
	//	//車体の移動量を加算
	//	judg.VecMatIn(&spark.Base.Mat, *CarMoveVec);
	//	for (int p = 0; p < PNum; p++) {
	//		judg.VecMatIn(&spark.PolMat[p], *CarMoveVec);
	//	}
	//}
	//else {
	//	CarMoveFlg = true;
	//}
	return true;
}

void C_Spark::Draw3DSpark(const D3DXVECTOR3 * CameraPos)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	spark.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	spark.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	spark.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	spark.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, spark.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	for (int i = 0; i < (PNum - 1); i++) {
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		Judg judg;
		judg.SetPosM(&nPos, &spark.m.Mat[i]);
		judg.SetPosM(&oPos, &spark.m.Mat[i + 1]);
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &PolSize);
		spark.v[0].Pos = nPos - vec;
		spark.v[1].Pos = nPos + vec;
		spark.v[2].Pos = oPos + vec;
		spark.v[3].Pos = oPos - vec;
		spark.v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(PNum - 1));
		spark.v[1].Tex = D3DXVECTOR2(1.0f, (float)i / (float)(PNum - 1));
		spark.v[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (float)(PNum - 1));
		spark.v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(PNum - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, spark.v, sizeof(VERTEX));//2はポリゴン数
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

bool C_Spark::CountUpdate(void)
{
	//一秒減らす
	NowCount -= 1;
	if (NowCount <=0) {
		//時間が経った
		NowCount = 0;
		return false;
	}
	return true;
}

void C_Spark::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	Draw3DSpark(CameraPos);
}
