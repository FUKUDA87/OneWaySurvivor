#include"SparkDamege.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
C_SparkDamage::C_SparkDamage(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos) :C_Spark(Mat, Pos)
{

}

C_SparkDamage::C_SparkDamage(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, const int * SparkFlg, const float *Ang) : C_Spark(Mat, Pos)
{
	DrawSDFlg = true;
	UpdateFlg = false;
	spark.Base.Mat = *Mat;
	Judg judg;
	judg.SetMatP(&spark.Base.Mat, Pos);

	//ポリゴンサイズの初期化
	PolSize = 0.03f;
	PolSizeSD = 0.025f;

	//衝突物の判定
	SparkJudgGround(Mat, Pos, SparkFlg);
	SparkJudgWall(Mat, Pos, SparkFlg);
	SparkJudgCar(Mat, Pos, SparkFlg, Ang);

	//スパークの初期化
	//フラッシュ
	Flash.Tex = textureManager.GetTexture("MuzFla1T.png", 128, 128, NULL);
	Flash.Base.Mat = *Mat;
	judg.SetMatP(&Flash.Base.Mat, Pos);
}

C_SparkDamage::~C_SparkDamage()
{
}

bool C_SparkDamage::Update(void)
{
	bool Flg;
	if (UpdateFlg == false) {
		Flg = UpdateSpark();
	}
	else {
		Flg = UpdateCar();
	}
	return Flg;
}

void C_SparkDamage::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Draw3DSpark(CameraPos);
	DrawSD(CameraPos);
}

bool C_SparkDamage::UpdateSD(void)
{
	Flash.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	Flash.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	Flash.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	Flash.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	Flash.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	Flash.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	Flash.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	Flash.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
	return true;
}

bool C_SparkDamage::UpdateCar(void)
{
	spark.Base.Mat._42 += yUp;
	//上移動と後ろ移動
	Judg judg;
	judg.SetMatP(&spark.Base.Mat, &(judg.SetPosM(&spark.Base.Mat) + spark.Base.Pos));
	//行列の更新
	for (int i = (PNum - 1); i > 0; i--) {
		spark.m.Mat[i] = spark.m.Mat[i - 1];
	}
	//先頭に一番新しい行列の代入
	spark.m.Mat[0] = spark.Base.Mat;
	yUp += yDown;
	return CountUpdate();
}

void C_SparkDamage::DrawSD(const D3DXVECTOR3 *CameraPos)
{
	if (DrawSDFlg == true) {
		UpdateSD();
		lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
		lpD3DDevice->SetTexture(0, Flash.Tex);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &Flash.Base.Mat);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
		//ビルボード
		D3DXVECTOR3 vec, oPos, nPos;
		D3DXMATRIX TransTmp;
		D3DXMatrixTranslation(&TransTmp, 0.0f, 1.0f*PolSizeSD, 0.0f);
		Judg judg;
		judg.SetPosM(&nPos, &(TransTmp*Flash.Base.Mat));
		D3DXMatrixTranslation(&TransTmp, 0.0f, -1.0f*PolSizeSD, 0.0f);
		judg.SetPosM(&oPos, &(TransTmp*Flash.Base.Mat));
		float L_Size = 3.0f*PolSizeSD;
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &L_Size);
		Flash.v[0].Pos = nPos - vec;
		Flash.v[1].Pos = nPos + vec;
		Flash.v[2].Pos = oPos + vec;
		Flash.v[3].Pos = oPos - vec;
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Flash.v, sizeof(VERTEX));//2はポリゴン数
		lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		DrawSDFlg = false;
	}

}

void C_SparkDamage::SparkJudgGround(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, const int * SparkFlg)
{
	if (*SparkFlg != 0)return;
	//回転
	D3DXMATRIX RotYMat, TransMat;
	float AngY;
	AngY = (float)(rand() % 45);
	if ((rand() % 2) == 1)AngY *= -1.0f;
	D3DXMatrixRotationY(&RotYMat, D3DXToRadian(AngY));
	Flash.Base.Mat = spark.Base.Mat;
	spark.Base.Mat = RotYMat * spark.Base.Mat;
	//時限の初期化
	NowCount = 1 * 5;
}

void C_SparkDamage::SparkJudgWall(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, const int * SparkFlg)
{
	if (*SparkFlg != 1)return;
	PNum = 2;
	//ポリゴン表示用のMatの初期化
	if (spark.m.Mat != nullptr) {
		delete[] spark.m.Mat;
	}
	spark.m.Mat = new D3DXMATRIX[PNum];
	//回転
	//X回転を求める
	int Big = 7000, Small = -4000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small) / 100.0f;
	int Mul = (int)Ang;
	if (Mul <= 0)Mul = 1;
	yDown = -0.05f - 0.003f*(float)Mul;
	//行列
	D3DXMATRIX RotYMat, TransMat, RotXMat;
	//壁の法線の方向
	D3DXMatrixRotationY(&RotYMat, D3DXToRadian(-90.0f));
	spark.Base.Mat = RotYMat * spark.Base.Mat;
	//乱数で出現方向を変える
	float AngY;
	AngY = (float)(rand() % 88);
	if ((rand() % 2) == 1)AngY *= -1.0f;
	D3DXMatrixRotationY(&RotYMat, D3DXToRadian(AngY));
	D3DXMatrixRotationX(&RotXMat, D3DXToRadian(Ang));
	spark.Base.Mat = RotXMat * RotYMat * spark.Base.Mat;

	yUp = 0.0f;
	zDown = -0.3f;

	PolSize = (float)(rand() % 3 + 3) / 100.0f;

	for (int i = 0; i < PNum; i++) {
		spark.m.Mat[i] = spark.Base.Mat;
	}

	//時限の初期化
	NowCount = 1 * 5;
	DrawSDFlg = true;

}

void C_SparkDamage::SparkJudgCar(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, const int * SparkFlg, const float *Ang)
{
	if (*SparkFlg != 2)return;
	//DrawSDFlg = false;
	PNum = 3;
	//ポリゴン表示用のMatの初期化
	if (spark.m.Mat != nullptr) {
		delete[] spark.m.Mat;
	}
	spark.m.Mat = new D3DXMATRIX[PNum];
	//時限の初期化
	NowCount = 1 * 2;
	//回転行列
	D3DXMATRIX RotZ, RotX;
	D3DXMatrixRotationZ(&RotZ, D3DXToRadian(*Ang));
	D3DXMatrixRotationX(&RotX, D3DXToRadian(30.0f));
	spark.Base.Mat = RotZ * RotX *spark.Base.Mat;

	yUp = 0.0f;
	zDown = (float)(rand() % 20 + 10) / 100.0f;
	yDown = -0.0f;

	//ベクトル計算
	D3DXVec3TransformNormal(&spark.Base.Pos, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &spark.Base.Mat);
	//spark.Base.Pos.y = 0.0f;
	D3DXVec3Normalize(&spark.Base.Pos, &spark.Base.Pos);
	spark.Base.Pos *= zDown;

	for (int i = 0; i < PNum; i++) {
		spark.m.Mat[i] = spark.Base.Mat;
	}

	/*UpdateCar();
	NowCount += 1;*/

	UpdateFlg = true;
	PolSizeSD = 0.001f;

	PolSize = 0.03f;
}