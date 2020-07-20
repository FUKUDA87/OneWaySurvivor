#include "Vector.h"
#include"../MaterialManager/TextureManager.h"
#include"../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト
#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height


void Vector::Init()
{
	vector.TEX = { NULL,500,593 };
	vector.TEX.Tex = textureManager.GetTexture("arrow008ZG3.png",
		vector.TEX.Width, vector.TEX.Height, NULL);
	float size = 0.8f;
	vector.Base.ScaPos = D3DXVECTOR2(100.0f/(float)vector.TEX.Width*0.25f*0.9f, 100.0f/(float)vector.TEX.Height*0.5f*0.9f);
	D3DXMatrixScaling(&vector.Base.Scal, vector.Base.ScaPos.x, vector.Base.ScaPos.y, 0);
	f = 0.0f;
	vector.Base.Pos = D3DXVECTOR2(SCRW / 2, SCRH / 2);
	//NowMat
	D3DXMATRIX Trans, Rot;
	D3DXMatrixTranslation(&NowTrans, SCRW / 2, SCRH / 2, NULL);
	NowAng = 0.0f;
	D3DXMatrixRotationZ(&Rot, D3DXToRadian(NowAng));
	NowMat = Rot * NowTrans;
	vector.Base.Flg = true;
	cou = new Cou(0, 20, 1, true, false);
	NowCount = 0;
	CountEnd = 5;

	//小さい版
	vectorC.TEX = { NULL,500,593 };
	vectorC.TEX.Tex = textureManager.GetTexture("arrow008ZG2.png",
		vectorC.TEX.Width, vectorC.TEX.Height, NULL);
	vectorC.Base.ScaPos = D3DXVECTOR2(100.0f / (float)vectorC.TEX.Width*0.25f*0.75f, 100.0f / (float)vectorC.TEX.Height*0.5f*0.75f);
	D3DXMatrixScaling(&vectorC.Base.Scal, vectorC.Base.ScaPos.x, vectorC.Base.ScaPos.y, 0);
}

Vector::~Vector()
{
	delete cou;
}

bool Vector::Update(const D3DXVECTOR3 *Pos_2D,const D3DXMATRIX *Mat,const D3DXVECTOR3 *CameraPos)
{
	D3DXVECTOR3 Pos = *Pos_2D;

	vector.Base.Flg = true;
	if ((Pos.z >= 0.0f) && (Pos.z <= 1.0f)) {
		if ((Pos.x>0) && (Pos.x<1280) && (Pos.y>0) && (Pos.y<720)) {
			vector.Base.Flg = false;
		}
	}else{
		//enemyベクトルの方向変え
		bool x;
		x = false;
		float px;
		px = 1280.0f / 2.0f;
		if (x == false) {
			if (Pos.x < px) {
				Pos.x = px + px - Pos.x;
				x = true;
			}
		}
		if (x == false) {
			if (Pos.x > px) {
				Pos.x = px + px - Pos.x;
				x = true;
			}
		}
		if (Mat->_42 < CameraPos->y) {
			float f = (float)(720 / 2);
			if ( f> Pos.y) {
				Pos.y = f;
			}
		}
	}
	//進化
	D3DXVECTOR2 NowPos, nVec,Pos2D,vec;
	NowPos = D3DXVECTOR2(NowMat._41, NowMat._42);
	Pos2D = D3DXVECTOR2(Pos.x, Pos.y);
	vec = D3DXVECTOR2(0.0f, 1.0f);
	D3DXVec2Normalize(&vec, &vec);
	D3DXVec2TransformCoord(&nVec, &vec, &NowMat);
	nVec = nVec - NowPos;
	D3DXVec2Normalize(&nVec, &nVec);
	//白の内積を求める
	float nowAng;
	nowAng = D3DXVec2Dot(&vec, &nVec);
	nowAng = D3DXToDegree(acos(nowAng));
	if (nVec.x > 0) {
		nowAng = -nowAng;
	}
	//
	D3DXVECTOR2 TargetVec;
	TargetVec = Pos2D - NowPos;
	D3DXVec2Normalize(&TargetVec, &TargetVec);
	float toAng;
	toAng = D3DXVec2Dot(&D3DXVECTOR2(0.0f,1.0f), &TargetVec);
	toAng = D3DXToDegree(acos(toAng));
	if (TargetVec.x > 0) {
		toAng = -toAng;
	}
	//
	float ang;
	if (isnan(nowAng)==false) {
		ang = toAng - nowAng;
	}
	else {
		nowAng = toAng;
		ang = 0.0f;
	}

	if (ang > 180.0f) ang -= 360.0f;
	if (ang < -180.0f)ang += 360.0f;

	float f = 4.0f;
	if (ang > f)ang = f;
	if (ang < -f)ang = -f;
	nowAng += ang;
	D3DXMATRIX rot;
	D3DXMatrixRotationZ(&vector.Base.RotZ, D3DXToRadian(nowAng));
	NowMat = vector.Base.RotZ*NowTrans;

	//線とレイ
	D3DXVECTOR2 NowVec;
	D3DXVec2TransformCoord(&NowVec, &D3DXVECTOR2(0, 700), &NowMat);
	NowVec = NowVec - NowPos;
	float Dis;
	D3DXVECTOR2 v[4];
	float x[2], y[2];
	x[0] = 0 + (vector.TEX.Height*vector.Base.ScaPos.y / 2.0f);
	x[1] = 1280 - (vector.TEX.Height*vector.Base.ScaPos.y / 2.0f);
	y[0] = 0 + (vector.TEX.Height*vector.Base.ScaPos.y / 2.0f);
	y[1] = 720 - (vector.TEX.Height*vector.Base.ScaPos.y / 2.0f);
	v[0] = D3DXVECTOR2(x[0], y[0]);
	v[1] = D3DXVECTOR2(x[1], y[0]);
	v[2] = D3DXVECTOR2(x[1], y[1]);
	v[3] = D3DXVECTOR2(x[0], y[1]);
	for (int i = 0; i < 4; i++) {
		D3DXVECTOR2 posA, vecA;
		int n = i + 1;
		if (i==3) {
			n = 0;
		}
		posA = v[i];
		vecA = v[n];
		Judg judg;
		if (judg.LineLine(NowPos, NowVec, posA, vecA, &Dis) == true) {
			vector.Base.Pos.x = NowPos.x + NowVec.x * Dis;
			vector.Base.Pos.y = NowPos.y + NowVec.y * Dis;
			break;
		}
	}
	//点滅表示
	/*if (NowCount < CountEnd) {
		if (cou->CouJudge() == true) {
			cou->CouUpd();
		}
		else {
			cou->SetNum(0);
			NowCount += 1;
			if (vector.Base.Flg == true) {
				if(NowCount < CountEnd){
					vector.Base.Flg = false;
				}
				else {
					vector.Base.Flg = true;
				}
			}
			else {
				vector.Base.Flg = true;
			}
		}
	}
	else {
		vector.Base.Flg = true;
	}*/
	return true;
}

void Vector::Draw(bool b)
{
	if (b != true)return;
		if (vector.Base.Flg == true) {
			RECT rcVec = { 0,0,vector.TEX.Width,vector.TEX.Height };
			D3DXMATRIX tmp;
			D3DXMatrixTranslation(&vector.Base.Mat, vector.Base.Pos.x, vector.Base.Pos.y, NULL);
			tmp = vector.Base.Scal*vector.Base.RotZ*vector.Base.Mat;
			lpSprite->SetTransform(&tmp);
			lpSprite->Draw(vector.TEX.Tex, &rcVec, &D3DXVECTOR3((float)vector.TEX.Width / 2.0f, (float)vector.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
				RECT rcVecC = { 0,0,vectorC.TEX.Width,vectorC.TEX.Height };
				D3DXMatrixTranslation(&vectorC.Base.Mat, vector.Base.Pos.x, vector.Base.Pos.y, NULL);
				tmp = vectorC.Base.Scal*vector.Base.RotZ*vectorC.Base.Mat;
				lpSprite->SetTransform(&tmp);
				lpSprite->Draw(vectorC.TEX.Tex, &rcVecC, &D3DXVECTOR3((float)vectorC.TEX.Width / 2.0f, (float)vectorC.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			
		}
}
