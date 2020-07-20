#include"Judgment.h"
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern HWND Hwnd;

bool Judg::BallJudg(const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB, const float * Radius)
{
	D3DXVECTOR3 targetPos;

	targetPos = (*PosB) - (*PosA);

	float length = D3DXVec3Length(&targetPos);

	if (length < *Radius) return true;

	return false;
}

bool Judg::BallJudg(float * SmallDis,const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB, const float * Radius, const bool *Flg)
{
	D3DXVECTOR3 targetPos;

	targetPos = (*PosB) - (*PosA);

	float length = D3DXVec3Length(&targetPos);

	if (length > *Radius)return false;

	float Dis = *Radius - length;

	if (*Flg == false) {
		*SmallDis = Dis;
		return true;
	}

	if (*SmallDis > Dis)return false;

	*SmallDis = Dis;

	return true;
}

bool Judg::ball(D3DXMATRIX mat1, D3DXMATRIX mat2, float rad,D3DXMATRIX *Trans1,D3DXMATRIX *Trans2)
{
	D3DXVECTOR3 pos1, pos2, targetPos;
	pos1 = D3DXVECTOR3(mat1._41, mat1._42, mat1._43);
	pos2 = D3DXVECTOR3(mat2._41, mat2._42, mat2._43);
	targetPos = pos2 - pos1;
	float length = D3DXVec3Length(&targetPos);
	if (length < rad) {
		D3DXVec3Normalize(&targetPos, &targetPos);
		targetPos *= (rad) - length;
		pos2 += targetPos;
		pos2.y = 0.0f;
		D3DXMatrixTranslation(Trans2, pos2.x, pos2.y, pos2.z);
		return true;
	}
	return false;
}

float Judg::BallJudg(const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB)
{
	D3DXVECTOR3 targetPos;

	targetPos = (*PosB) - (*PosA);

	return D3DXVec3Length(&targetPos);
}

bool Judg::Pop_BallJudg(const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB, const float * Radius)
{
	D3DXVECTOR3 pA = *PosA,
		        pB = *PosB;

	pA.y = 0.0f;

	pB.y = 0.0f;

	//球判定
	return BallJudg(&pA, &pB, Radius);
}

bool Judg::HPj(int *NowHp, int *NowMaxHp)
{
	if (*NowHp < 0) {
		*NowHp = 0;
		return false;
	}
	else {
		if (*NowHp > *NowMaxHp) {
			*NowHp = *NowMaxHp;
		}
	}
	return true;
}

bool Judg::RayJudg_Polygon(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec,
	const D3DXVECTOR3 * vA, const D3DXVECTOR3 * vB, const D3DXVECTOR3 * vC, const D3DXVECTOR3 * vD, float *Dis)
{
	//レイ方向
	D3DXVECTOR3 L_RayVec = *Ray_Vec;

	D3DXVec3Normalize(&L_RayVec, &L_RayVec);

	//レイが当たった長さ
	float L_Dis;

	if (D3DXIntersectTri(vA, vB, vC, Ray_Pos, &L_RayVec, NULL, NULL, &L_Dis) ||
		D3DXIntersectTri(vA, vC, vD, Ray_Pos, &L_RayVec, NULL, NULL, &L_Dis)) {

		if (Dis != nullptr)*Dis = L_Dis;

		return true;

	}

	return false;
}

bool Judg::RayJudg_Polygon(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, const D3DXMATRIX * Polygon_Mat,
	const D3DXVECTOR3 * vA, const D3DXVECTOR3 * vB, const D3DXVECTOR3 * vC, const D3DXVECTOR3 * vD, float * Dis)
{
	D3DXVECTOR3 VPos[4];
	D3DXVec3TransformCoord(&VPos[0], vA, Polygon_Mat);
	D3DXVec3TransformCoord(&VPos[1], vB, Polygon_Mat);
	D3DXVec3TransformCoord(&VPos[2], vC, Polygon_Mat);
	D3DXVec3TransformCoord(&VPos[3], vD, Polygon_Mat);

	//レイ判定
	return RayJudg_Polygon(Ray_Pos, Ray_Vec, &VPos[0], &VPos[1], &VPos[2], &VPos[3], Dis);
}

bool Judg::RayJudg_Polygon_SmallDis(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, const D3DXMATRIX * Polygon_Mat,
	const D3DXVECTOR3 * vA, const D3DXVECTOR3 * vB, const D3DXVECTOR3 * vC, const D3DXVECTOR3 * vD, float * Small_Dis)
{
	if (Small_Dis == nullptr)return false;

	float Dis;

	if (RayJudg_Polygon(Ray_Pos, Ray_Vec, Polygon_Mat, vA, vB, vC, vD, &Dis) == true) {

		if (*Small_Dis > Dis) {
			*Small_Dis = Dis;
			return true;
		}

	}

	return false;
}

bool Judg::RayJudg_Polygon_SmallDis(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec,
	const D3DXVECTOR3 * vA, const D3DXVECTOR3 * vB, const D3DXVECTOR3 * vC, const D3DXVECTOR3 * vD, float * Small_Dis)
{
	if (Small_Dis == nullptr)return false;

	float Dis;

	if (RayJudg_Polygon(Ray_Pos, Ray_Vec, vA, vB, vC, vD, &Dis) == true) {

		if (*Small_Dis > Dis) {
			*Small_Dis = Dis;
			return true;
		}

	}
	
	return false;
}

bool Judg::RayJudg_Polygon(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, const D3DXMATRIX * Polygon_Mat,
	const D3DXVECTOR3 * vA, const D3DXVECTOR3 * vB, const D3DXVECTOR3 * vC, const D3DXVECTOR3 * vD, float * Dis,
	const bool * Judg_Type_IdenMat)
{
	if (*Judg_Type_IdenMat == true)return RayJudg_Polygon(Ray_Pos, Ray_Vec, vA, vB, vC, vD, Dis);

	return RayJudg_Polygon(Ray_Pos, Ray_Vec, Polygon_Mat, vA, vB, vC, vD, Dis);
}

void Judg::Pos2D(D3DXVECTOR3 * Pos_2D, const D3DXVECTOR3 * Pos3D, const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	D3DXVec3Project(Pos_2D, Pos3D, Viewport, mProj, mView, &IdenMat);
}

void Judg::Pos2DPE(D3DXVECTOR3 * Pos_2D, const D3DXMATRIX * eMat, const D3DXMATRIX * pMat, const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	D3DXVECTOR3 EPos;

	EPos = D3DXVECTOR3(eMat->_41, eMat->_42, eMat->_43);
	Pos2D(Pos_2D,&EPos,mProj,mView,Viewport);

	if ((Pos_2D->z >= 0.0f) && (Pos_2D->z <= 1.0f)) return;

	//playerからみて逆の位置のenemy
	D3DXVECTOR3 PPos, vec;
	PPos = D3DXVECTOR3(pMat->_41, pMat->_42, pMat->_43);
	vec = PPos - EPos;
	EPos = PPos + vec;
	EPos.y = eMat->_42;
	Pos2D(Pos_2D, &EPos, mProj, mView, Viewport);
	Pos_2D->z = 2.0f;
}

double Judg::Ang(D3DXVECTOR3 pla,D3DXVECTOR3 tar,D3DXVECTOR3 vec)
{
	//playerの方に向くtargetの計算---------------------------------------------------
	//2が向いているベクトル
	D3DXVECTOR3 Vec;
	D3DXMATRIX Pla;
	D3DXMatrixTranslation(&Pla, pla.x, pla.y, pla.z);
	D3DXVec3TransformNormal(&Vec, &vec, &Pla);
	//白の内積を求める
	double nowAng;
	nowAng = D3DXVec3Dot(&vec, &Vec);
	nowAng = D3DXToDegree(acos(nowAng));
	if (Vec.x < 0) {
		nowAng = -nowAng;
	}
	//
	D3DXVECTOR3 kPos, pPos, TargetVec;
	TargetVec = tar - pla;
	D3DXVec3Normalize(&TargetVec, &TargetVec);
	double toAng;
	toAng = D3DXVec3Dot(&vec, &TargetVec);
	toAng = D3DXToDegree(acos(toAng));
	if (TargetVec.x < 0) {
		toAng = -toAng;
	}
	//
	double ang;
	ang = toAng - nowAng;

	if (ang > 180.0f) ang -= 360.0f;
	if (ang < -180.0f)ang += 360.0f;

	//float f = 3.0f;
	//if (ang > f)ang = f;
	//if (ang < -f)ang = -f;
	//D3DXMatrixRotationY(&katsuoRot, D3DXToRadian(ang));

	return ang;
}

bool Judg::RayJudg_Mesh(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, const D3DXMATRIX * Draw_Mat, const LPD3DXMESH Mesh, float * Dis)
{
	//セットする
	D3DXMATRIX InvMat;

	D3DXMatrixInverse(&InvMat, NULL, Draw_Mat);

	D3DXVECTOR3 LocalPos, LocalVec;

	D3DXVec3TransformCoord(&LocalPos, Ray_Pos, &InvMat);

	D3DXVec3TransformNormal(&LocalVec, Ray_Vec, &InvMat);
	
	BOOL Hit;
	float L_Dis;

	//レイ判定
	D3DXIntersect(Mesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &L_Dis, NULL, NULL);

	if (Hit != TRUE)return false;

	if (Dis != nullptr)*Dis = L_Dis;

	return true;
}

int Judg::RayJudg_Mesh_PolNum(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, const D3DXMATRIX * Draw_Mat, const LPD3DXMESH Mesh, float * Dis)
{
	//セットする
	D3DXMATRIX InvMat;

	D3DXMatrixInverse(&InvMat, NULL, Draw_Mat);

	D3DXVECTOR3 LocalPos, LocalVec;

	D3DXVec3TransformCoord(&LocalPos, Ray_Pos, &InvMat);

	D3DXVec3TransformNormal(&LocalVec, Ray_Vec, &InvMat);

	BOOL Hit;
	float L_Dis;
	DWORD Hit_PolNum;

	//レイ判定
	D3DXIntersect(Mesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &L_Dis, NULL, &Hit_PolNum);

	if (Hit != TRUE)return 0;

	if (Dis != nullptr)*Dis = L_Dis;

	return (int)Hit_PolNum;
}

bool Judg::RayJudg_Mesh_SmallDis(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, const D3DXMATRIX * Draw_Mat, const LPD3DXMESH Mesh, float * Small_Dis)
{
	float L_Dis;

	//レイ判定
	if (RayJudg_Mesh(Ray_Pos, Ray_Vec, Draw_Mat, Mesh, &L_Dis) != true)return false;

	if (*Small_Dis > L_Dis) {
		*Small_Dis = L_Dis;
		return true;
	}

	return false;
}

bool Judg::CroDot(D3DXMATRIX mat, D3DXMATRIX *rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec, double *Ang, double ang, bool angF)
{
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVECTOR3 TargetPos;
	D3DXVec3TransformCoord(&TargetPos, &targetPos, &InvMat);
	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	float Dot;
	Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
	if (Dot > 1)Dot = 1;
	if (Dot < -1)Dot = -1;
	*Ang = D3DXToDegree(acos(Dot));
	if (angF == true) {
		if (*Ang > ang)*Ang = ang;
	}
	D3DXMatrixRotationAxis(rot, &RotAxis, D3DXToRadian((float)*Ang));
	return true;
}

bool Judg::TarRotX(D3DXMATRIX mat, D3DXMATRIX * rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec)
{
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVECTOR3 TargetPos;
	D3DXVec3TransformCoord(&TargetPos, &targetPos, &InvMat);
	//TargetPos.y = 0;
	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	double Dot,Ang;
	Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
	if (Dot > 1)Dot = 1;
	if (Dot < -1)Dot = -1;
	Ang = D3DXToDegree(acos(Dot));
	D3DXMatrixRotationAxis(rot, &RotAxis, D3DXToRadian((float)Ang));
	return true;
}

bool Judg::TarRotY(D3DXMATRIX mat,D3DXMATRIX *rotY, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec)
{
	mat._42 = 0.0f;
	targetPos.y = 0.0f;
	FrontVec.y = 0.0f;
	//playerの方に向くカツオの計算
	//カツオが向いているベクトル
	D3DXVECTOR3 kVec;
	D3DXVec3TransformNormal(&kVec, &FrontVec, &mat);
	//白の内積を求める
	double nowAng;
	nowAng = D3DXVec3Dot(&FrontVec, &kVec);
	nowAng = D3DXToDegree(acos(nowAng));
	if (kVec.x < 0) {
		nowAng = -nowAng;
	}
	//
	D3DXVECTOR3 kPos, pPos, TargetVec;
	kPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	pPos = targetPos;
	TargetVec = pPos - kPos;
	TargetVec.y = 0.0f;
	D3DXVec3Normalize(&TargetVec, &TargetVec);
	double toAng;
	toAng = D3DXVec3Dot(&FrontVec, &TargetVec);
	toAng = D3DXToDegree(acos(toAng));
	if (TargetVec.x < 0) {
		toAng = -toAng;
	}
	//
	double angs;
	angs = toAng - nowAng;

	if (angs > 180.0f) angs -= 360.0f;
	if (angs < -180.0f)angs += 360.0f;

	D3DXMatrixRotationY(rotY, D3DXToRadian((float)angs));
	return true;
}

bool Judg::TarEndMat(D3DXMATRIX * mat, D3DXMATRIX TransMat, D3DXMATRIX * RotXMat, D3DXMATRIX * RotYMat, D3DXVECTOR3 TargetPos, D3DXVECTOR3 FrontVec)
{
	D3DXMATRIX Mat;
	Mat = TransMat;
	TarRotY(Mat, RotYMat, TargetPos, FrontVec);
	Mat = (*RotYMat)*Mat;
	TarRotX(Mat, RotXMat, TargetPos, FrontVec);
	Mat = (*RotXMat)*Mat;
	*mat = Mat;
	return true;
}

D3DXVECTOR3 Judg::SetPosM(const D3DXMATRIX * Mat)
{
	return D3DXVECTOR3(Mat->_41, Mat->_42, Mat->_43);
}

D3DXVECTOR2 Judg::SetPos2DM(const D3DXMATRIX * Mat)
{
	return D3DXVECTOR2(Mat->_41, Mat->_42);
}

void Judg::SetPosM(D3DXVECTOR3 * Pos, const D3DXMATRIX * Mat)
{
	*Pos = D3DXVECTOR3(Mat->_41, Mat->_42, Mat->_43);
}

D3DXMATRIX Judg::SetMatP(const D3DXVECTOR3 *Pos)
{
	D3DXMATRIX Mat;

	SetMatP(&Mat,Pos);

	return Mat;
}

void Judg::SetMatP(D3DXMATRIX * Mat,const D3DXVECTOR3 *Pos)
{
	Mat->_41 = Pos->x;
	Mat->_42 = Pos->y;
	Mat->_43 = Pos->z;
}

void Judg::setTransMat(D3DXMATRIX * TransMat, const D3DXVECTOR3 * TransPos)
{
	D3DXMatrixTranslation(TransMat, TransPos->x, TransPos->y, TransPos->z);
}

void Judg::setTransMat(D3DXMATRIX * TransMat, const D3DXVECTOR2 * TransPos)
{
	D3DXMatrixTranslation(TransMat, TransPos->x, TransPos->y, NULL);
}

D3DXMATRIX Judg::getTransMat(const D3DXVECTOR3 * TransPos)
{
	D3DXMATRIX TransMat;

	setTransMat(&TransMat, TransPos);

	return TransMat;
}

D3DXMATRIX Judg::getTransMat(const D3DXVECTOR2 * TransPos)
{
	D3DXMATRIX TransMat;

	setTransMat(&TransMat, TransPos);

	return TransMat;
}

bool Judg::AnimeProc(D3DXMATRIX * NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float AnimeFrame)
{
	D3DXQUATERNION StartQua, EndQua, NowQua;
	D3DXQuaternionRotationMatrix(&StartQua, &StartMat);
	D3DXQuaternionRotationMatrix(&EndQua, &EndMat);
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, AnimeFrame);
	D3DXMatrixRotationQuaternion(NowMat, &NowQua);

	D3DXVECTOR3 StartPos, EndPos, NowPos;
	SetPosM(&StartPos, &StartMat);
	SetPosM(&EndPos,&EndMat);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, AnimeFrame);
	SetFloatQ(&NowPos);
	SetMatP(NowMat, &NowPos);
	return true;
}

void Judg::AnimeQua(D3DXMATRIX * NowMat, const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat, const float * AnimeFrame)
{
	D3DXQUATERNION StartQua, EndQua, NowQua;
	D3DXQuaternionRotationMatrix(&StartQua, StartMat);
	D3DXQuaternionRotationMatrix(&EndQua, EndMat);
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, *AnimeFrame);
	D3DXMatrixRotationQuaternion(NowMat, &NowQua);
}

bool Judg::AnimeProc(D3DXVECTOR3 * NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float AnimeFrame)
{
	D3DXVec3Lerp(NowPos, &StartPos, &EndPos, AnimeFrame);
	return true;
}

bool Judg::AnimeFrameInc(float * AnimeFrame, float up, bool upFlg)
{
	if (upFlg == true) {
		*AnimeFrame += up;
	}
	if (*AnimeFrame < 0.0f) {
		*AnimeFrame = 0.0f;
		return false;
	}
	if (*AnimeFrame > 1.0f) {
		*AnimeFrame = 1.0f;
		return false;
	}
	return true;
}

bool Judg::AnimeFrameInc(float * AnimeFrame, const float * up, const bool * FrameMoveFlg)
{
	if (*FrameMoveFlg != true)return false;

	//フレームに変化
	*AnimeFrame += *up;

	if (*AnimeFrame < 0.0f) {
		*AnimeFrame = 0.0f;
		return true;
	}

	if (*AnimeFrame > 1.0f) {
		*AnimeFrame = 1.0f;
		return true;
	}

	return false;
}

bool Judg::Quaternion(D3DXMATRIX * NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float * AnimeFrame, float up, bool upFlg)
{
	bool Flg;
	Flg=AnimeFrameInc(AnimeFrame, up, upFlg);
	AnimeProc(NowMat,StartMat,EndMat,*AnimeFrame);
	return Flg;
}

bool Judg::Quaternion(D3DXVECTOR3 * NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float * AnimeFrame, float up, bool upFlg)
{
	bool Flg;
	Flg = AnimeFrameInc(AnimeFrame, up, upFlg);
	AnimeProc(NowPos, StartPos, EndPos, *AnimeFrame);
	return Flg;
}

bool Judg::Quaternion(D3DXVECTOR2 * NowPos, D3DXVECTOR2 StartPos, D3DXVECTOR2 EndPos, float * AnimeFrame, float up, bool upFlg)
{
	bool Flg;
	Flg = AnimeFrameInc(AnimeFrame, up, upFlg);
	D3DXVec2Lerp(NowPos, &StartPos, &EndPos, *AnimeFrame);
	return Flg;
}

D3DXVECTOR3 Judg::DisPos(D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, float Dis)
{
	D3DXVECTOR3 PosD,Vec;
	Vec = PosB - PosA;
	D3DXVec3Normalize(&Vec, &Vec);
	PosD = PosA + Vec * Dis;
	return PosD;
}

D3DXVECTOR3 Judg::Billboard(const D3DXVECTOR3 * OldPos, const D3DXVECTOR3 * NowPos, const D3DXVECTOR3 * camPos, const float * Size)
{
	D3DXVECTOR3 cVec, eVec, vec;
	cVec = *camPos - *OldPos;
	eVec = *NowPos - *OldPos;
	D3DXVec3Normalize(&cVec, &cVec);
	D3DXVec3Normalize(&eVec, &eVec);
	D3DXVec3Cross(&vec, &cVec, &eVec);
	D3DXVec3Normalize(&vec, &vec);
	vec = vec * (*Size);
	return vec;
}

D3DXVECTOR3 Judg::Billboard(const D3DXVECTOR3 *OldPos, const D3DXVECTOR3 *NowPos,const D3DXVECTOR3 *CameraPos, const float *Size,const bool *Reverse)
{
	D3DXVECTOR3 LPos, EPos, CPos, cVec, eVec, vec;
	LPos = *OldPos;
	EPos = *NowPos;
	CPos = *CameraPos;
	if (*Reverse == false) {
		cVec = CPos - LPos;
		eVec = EPos - LPos;
	}
	else {
		cVec = CPos - EPos;
		eVec = LPos - EPos;
	}
	D3DXVec3Normalize(&cVec, &cVec);
	D3DXVec3Normalize(&eVec, &eVec);
	D3DXVec3Cross(&vec, &cVec, &eVec);
	D3DXVec3Normalize(&vec, &vec);
	vec = vec * (*Size);
	return vec;
}

bool Judg::LineLine(const D3DXVECTOR2 PosA, const D3DXVECTOR2 VecA, const D3DXVECTOR2 PosB, const D3DXVECTOR2 VecB, float * Dis)
{
	D3DXVECTOR2 posA, posB, vecA, vecB;
	posA = PosA;
	vecA = VecA;

	posB = PosB;
	vecB = VecB;

	//線の法線を調べます。座標ベクトル B から座標ベクトル A を引いてベクトルABを求めます。
	D3DXVECTOR2 pvB;
	pvB = vecB - posB;

	//時計回りに90度回転します。
	D3DXVECTOR2 n;
	n = D3DXVECTOR2(-pvB.y, pvB.x);

	//法線を正規化します。
	D3DXVec2Normalize(&n, &n);


	//とりあえず下の式で t が求まります。
	float d;
	d = -(posB.x * n.x + posB.y * n.y);
	*Dis = -(n.x * posA.x + n.y * posA.y + d) / (n.x * vecA.x + n.y * vecA.y);
	if ((*Dis > 0.0f) && (*Dis <= 1.0f)) {

	}
	else {
		return false;
	}

	//点が線に含まれているかどうか。
	D3DXVECTOR2 posC;
	posC = posA + vecA * (*Dis);
	D3DXVECTOR2 acVec, bcVec;
	acVec = posC - posB;
	bcVec = posC - vecB;
	float Dot;
	Dot = (acVec.x * bcVec.x) + (acVec.y * bcVec.y);

	if ((Dot < 0.0f)) {
		return true;
	}
	return false;
}

D3DXVECTOR2 Judg::HalfSize(const D3DXVECTOR3 sPos, const int Width, const int Height)
{
	D3DXVECTOR2 Pos;
	Pos =D3DXVECTOR2((float)Width / 2.0f*sPos.x,(float)Height / 2.0f*sPos.y);
	return Pos;
}

bool Judg::PlaneP(RECT * rc, const D3DXVECTOR2 * Pos, const D3DXVECTOR2 * scalSize, const int * Width, const int * Height)
{
	D3DXVECTOR2 PosL, PosR, size;
	size = D3DXVECTOR2((float)*Width *scalSize->x, (float)*Height *scalSize->y);
	size /= 2.0f;
	PosL = *Pos - size;
	PosR = *Pos + size;
	*rc = { (int)PosL.x,(int)PosL.y,(int)PosR.x,(int)PosR.y };
	return true;
}

bool Judg::PlaneCri(const D3DXVECTOR2 * Pos, const D3DXVECTOR2 * scalSize, const int * Width, const int * Height)
{
	RECT rcM;
	PlaneP(&rcM, Pos, scalSize, Width, Height);
	POINT Pt;
	Pt = GetPoint();
	if ((Pt.x > rcM.left) && (Pt.x < rcM.right) && (Pt.y > rcM.top) && (Pt.y < rcM.bottom)) {
		return true;
	}
	return false;
}

bool Judg::PlaneCri(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * scalSize, const int * Width, const int * Height)
{
	RECT rcM;
	D3DXVECTOR2 pos = D3DXVECTOR2(Pos->x, Pos->y), scal = D3DXVECTOR2(scalSize->x, scalSize->y);
	PlaneP(&rcM, &pos, &scal, Width, Height);
	POINT Pt;
	Pt = GetPoint();
	if ((Pt.x > rcM.left) && (Pt.x < rcM.right) && (Pt.y > rcM.top) && (Pt.y < rcM.bottom)) {
		return true;
	}
	return false;
}

POINT Judg::GetPoint(void)
{
	POINT Pt;
	GetCursorPos(&Pt);
	ScreenToClient(Hwnd, &Pt);
	return Pt;
}

bool Judg::LineLine3D(D3DXVECTOR3 * GetPos, D3DXVECTOR3 PosA1, D3DXVECTOR3 PosA2, D3DXVECTOR3 PosB1, D3DXVECTOR3 PosB2)
{
	//交差判定------------------------------------------------------------------
	/*bool Flg;
	if ((D3DXToDegree(acos(D3DXVec3Dot(&(PosA2 - PosA1), &(PosB1 - PosA1))))*D3DXToDegree(acos(D3DXVec3Dot(&(PosA2 - PosA1), &(PosB2 - PosA1)))) < 0.0f) &&
		(D3DXToDegree(acos(D3DXVec3Dot(&(PosB2 - PosB1), &(PosA1 - PosB1))))*D3DXToDegree(acos(D3DXVec3Dot(&(PosB2 - PosB1), &(PosA2 - PosB1)))) < 0.0f)) {
		Flg = true;
	}
	else {
		return false;
	}*/
	//交点----------------------------------------------------------------------
	D3DXVECTOR3 b = PosB2 - PosB1,b2,b3,s1,s2;
	D3DXVec3Normalize(&b, &b);
	D3DXVec3Normalize(&b2, &(PosA1 - PosB1));
	D3DXVec3Cross(&s1, &b, &b2);
	double d1 = D3DXVec3Length(&s1);
	if (d1 < 0.0f) {
		d1 = d1*(-1.0f);
	}
	//if (d1 > 1.0f)d1 = 1.0f;
	//d1 = D3DXToDegree(acos(d1));
	D3DXVec3Normalize(&b3, &(PosA2 - PosB1));
	D3DXVec3Cross(&s2,&b, &b3);
	double d2 = D3DXVec3Length(&s2);
	if (d2 < 0.0f) {
		d2 = d2*(-1.0f);
	}
	//if (d2 > 1.0f)d2 = 1.0f;
	//d2 = D3DXToDegree(acos(d2));
	double t = d2 / (d2 + d1);//-------------------------------------

	D3DXVECTOR3 e = PosB1 - PosB2, e2, e3;
	D3DXVec3Normalize(&e, &e);
	D3DXVec3Normalize(&e2, &(PosA1 - PosB2));
	double f1 = D3DXVec3Dot(&e, &e2);
	if (f1 < 0.0f) {
		f1 = f1 * (-1.0f);
	}
	//if (d1 > 1.0f)d1 = 1.0f;
	f1 = D3DXToDegree(acos(f1));
	D3DXVec3Normalize(&e3, &(PosA2 - PosB2));
	double f2 = D3DXVec3Dot(&e, &e3);
	if (f2 < 0.0f) {
		f2 = f2 * (-1.0f);
	}
	//if (d2 > 1.0f)d2 = 1.0f;
	f2 = D3DXToDegree(acos(f2));
	double u = f1 / (f1 + f2);//------------------------------------
	double o = u - t;
	o = o / 2.0f;

	*GetPos= PosA1 + (PosA2 - PosA1) * ((float)t);
	//線と点判定----------------------------------------------------------------
	/*D3DXVECTOR3 acVec, bcVec;
	acVec = *GetPos - PosA1;
	bcVec = *GetPos - PosA2;
	float Dot;
	Dot = (acVec.x * bcVec.x) + (acVec.y * bcVec.y)+ (acVec.z * bcVec.z);
	if ((Dot < 0.0f)) {
		return true;
	}*/
	return false;
}

bool Judg::SetppMat(D3DXMATRIX * Mat, D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, D3DXVECTOR3 PosC, int RailNum, bool bc)
{
	if ((RailNum != 5)) {
		return false;
	}
	D3DXVECTOR3 Vec, Pos;
	Vec = PosB - PosA;
	Vec /= 2.0f;
	SetMatP(&Mat[2], &(PosA + Vec));
	D3DXVec3Normalize(&Vec, &Vec);
	SetPosM(&Pos, &Mat[2]);
	SetMatP(&Mat[1], &(Pos + -(Vec*5.0f)));
	SetMatP(&Mat[0], &(Pos + -(Vec * 10.0f)));
	SetMatP(&Mat[3], &(Pos + (Vec * 5.0f)));
	SetMatP(&Mat[4], &(Pos + (Vec * 10.0f)));

	float f = 2.0f;
	if (bc == true) {
		Vec = PosC - PosB;
	}
	else {
		Vec = PosC - PosA;
	}
	//D3DXVec3Normalize(&Vec, &Vec);
	Vec /= f;
	for (int i = 0; i < RailNum; i++) {
		SetPosM(&Pos, &Mat[i]);
		Pos += Vec;
		SetFloatQ(&Pos);
		SetMatP(&Mat[i], &Pos);
	}
	return true;
}

bool Judg::MatMatVec(D3DXVECTOR3 * Vec, D3DXMATRIX MatA, D3DXMATRIX MatB)
{
	D3DXVECTOR3 PosA, PosB;
	SetPosM(&PosA, &MatA);
	SetPosM(&PosB, &MatB);
	*Vec = PosB - PosA;
	return true;
}

D3DXVECTOR3 Judg::MatMatVec(D3DXMATRIX MatA, D3DXMATRIX MatB)
{
	D3DXVECTOR3 PosA, PosB;
	SetPosM(&PosA, &MatA);
	SetPosM(&PosB, &MatB);
	PosA = PosB - PosA;
	return PosA;
}

bool Judg::VecMatIn(D3DXMATRIX * Mat,const D3DXVECTOR3 *Vec)
{
	D3DXVECTOR3 Pos;
	SetPosM(&Pos, Mat);
	Pos += *Vec;
	SetMatP(Mat, &Pos);
	return true;
}

bool Judg::SetFloatQ(float *f)
{
	(*f)=(float)((int)((*f)*1000.0f)) / 1000.0f;
	return true;
}

bool Judg::SetFloatQ(D3DXVECTOR3 *Pos)
{
	SetFloatQ(&Pos->x);
	SetFloatQ(&Pos->y);
	SetFloatQ(&Pos->z);
	return true;
}

float Judg::SlashFloat(float fA, float fB)
{
	int iA, iB;
	iA = ((int)(fA*1000.0f)) * 1000;
	iB = (int)(fB*1000.0f);
	return ((float)(iA/iB)/1000.0f);
}

void Judg::Ads(float * f)
{
	if (*f < 0.0f)*f *= -1.0f;
}

void Judg::Ads(D3DXVECTOR3 * p)
{
	Ads(&p->x);
	Ads(&p->y);
	Ads(&p->z);
}

bool Judg::Big(float * fa, const float * fb)
{
	if (*fa < *fb)*fa = *fb;

	return true;
}

bool Judg::Big(float * f, const float * fa, const float * fb)
{
	if (*fa > *fb)
	{
		*f = *fa;
	}
	else {
		*f = *fb;
	}

	return true;
}

bool Judg::Big(D3DXVECTOR3 * p, const D3DXVECTOR3 * pa, const D3DXVECTOR3 * pb)
{
	Big(&p->x, &pa->x, &pb->x);
	Big(&p->y, &pa->y, &pb->y);
	Big(&p->z, &pa->z, &pb->z);

	return true;
}

bool Judg::Big(D3DXVECTOR3 * BigVec, const D3DXVECTOR3 * p)
{
	Big(&BigVec->x, &p->x);
	Big(&BigVec->y, &p->y);
	Big(&BigVec->z, &p->z);

	return true;
}

bool Judg::Small(float * fa, const float * fb)
{
	if (*fa > *fb)*fa = *fb;

	return true;
}

bool Judg::Small(D3DXVECTOR3 * SmallVec, const D3DXVECTOR3 * p)
{
	Small(&SmallVec->x, &p->x);
	Small(&SmallVec->y, &p->y);
	Small(&SmallVec->z, &p->z);

	return true;
}

float Judg::GetRad(XFILE_B * MeshData)
{
	D3DXVECTOR3 pos, bigVec, smallVec;
	bigVec = MeshData->Data.BigVec;
	smallVec = MeshData->Data.SmallVec;
	
	Ads(&bigVec);
	Ads(&smallVec);

	Big(&pos, &bigVec, &smallVec);

	return D3DXVec3Length(&pos);
}

void Judg::ReverseFlg(bool * Flg)
{
	if (*Flg == true) {
		*Flg = false;
	}
	else {
		*Flg = true;
	}
}

bool Judg::ReverseFlg2(const bool * Flg)
{
	if (*Flg == true) {
		return false;
	}
	else {
		return true;
	}
	return false;
}

int Judg::Reverse(const bool * Flg)
{
	if (*Flg == true)return -1;

	return 1;
}

void Judg::setScalingMat(D3DXMATRIX * ScalMat, const D3DXVECTOR3 * Pos)
{
	D3DXMatrixScaling(ScalMat, Pos->x, Pos->y, Pos->z);
}

void Judg::setScalingMat(D3DXMATRIX * ScalMat, const D3DXVECTOR2 * Pos)
{
	D3DXMatrixScaling(ScalMat, Pos->x, Pos->y, NULL);
}

D3DXMATRIX Judg::getScalingMat(const D3DXVECTOR3 * Pos)
{
	D3DXMATRIX Mat;
	D3DXMatrixScaling(&Mat, Pos->x, Pos->y, Pos->z);
	return Mat;
}

D3DXMATRIX Judg::getScalingMat(const D3DXVECTOR2 * Pos)
{
	D3DXMATRIX Mat;
	D3DXMatrixScaling(&Mat, Pos->x, Pos->y, NULL);
	return Mat;
}

void Judg::InitRotX(const D3DXMATRIX * Mat,D3DXMATRIX * RotX)
{
	//今の行列
	D3DXMATRIX nMat=*Mat;
	D3DXVECTOR3 pVec, ppVec;
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &nMat);
	ppVec = pVec;

	float Dot, Ang;

	//RotYの計算
	D3DXMATRIX CamRotY, CamRotX;
	ppVec.y = 0;
	//内積
	Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &ppVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = (float)D3DXToDegree(acos(Dot));
	if (ppVec.x < 0.0f)Ang *= -1.0f;
	D3DXMatrixRotationY(&CamRotY, D3DXToRadian(-Ang));


	//RotXの計算
	nMat = CamRotY * nMat;
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &nMat);
	//内積
	Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &pVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = (float)D3DXToDegree(acos(Dot));
	if (pVec.y > 0.0f)Ang *= -1.0f;
	D3DXMatrixRotationX(&CamRotX, D3DXToRadian(Ang));
	*RotX = CamRotX;
}

QuaAnimeC Judg::InitQuaAnime(const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat, const float * NowAnime, const float * AnimeFrame)
{
	QuaAnimeC qa;
	qa.NowMat = qa.StartMat = *StartMat;
	qa.EndMat = *EndMat;
	qa.NowAnime = *NowAnime;
	qa.AnimeFrame = *AnimeFrame;
	return qa;
}

void Judg::InitMatPos(D3DXMATRIX * Mat, D3DXVECTOR3 * TransPos, D3DXVECTOR3 * ScalPos)
{
	D3DXMatrixTranslation(Mat, 0.0f, 0.0f, 0.0f);
	*TransPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	*ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

D3DXMATRIX Judg::GetDrawMat(const D3DXMATRIX * Mat,D3DXMATRIX * ScalMat, const D3DXVECTOR3 * ScalPos)
{
	setScalingMat(ScalMat, ScalPos);
	D3DXMATRIX Tmp = *Mat;
	Tmp = *ScalMat*Tmp;
	return Tmp;
}

D3DXMATRIX Judg::GetDrawMat(const D3DXMATRIX * Mat, const D3DXVECTOR3 * ScalPos)
{
	D3DXMATRIX Tmp;

	setScalingMat(&Tmp, ScalPos);

	Tmp = Tmp * (*Mat);

	return Tmp;
}

BASE3D Judg::GetInitBase3D(const D3DXVECTOR3 * InitPos, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos, const double * AngX, const  double * AngY, const  double * AngZ)
{
	BASE3D b;

	b.Pos = *InitPos;
	setTransMat(&b.Mat, &b.Pos);
	b.TraPos = *TransPos;
	setTransMat(&b.Trans, &b.TraPos);
	b.ScaPos = *ScalPos;
	setScalingMat(&b.Scal, &b.ScaPos);

	b.AngX = *AngX;
	D3DXMatrixRotationX(&b.RotX, D3DXToRadian((float)b.AngX));
	b.AngY = *AngY;
	D3DXMatrixRotationY(&b.RotY, D3DXToRadian((float)b.AngY));
	b.AngZ = *AngZ;
	D3DXMatrixRotationZ(&b.RotZ, D3DXToRadian((float)b.AngZ));

	return b;
}

D3DXMATRIX Judg::GetTransMatScal(const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos)
{
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, TransPos->x*ScalPos->x, TransPos->y*ScalPos->y, TransPos->z*ScalPos->z);
	return Tmp;
}

void Judg::Get_TransMatScal(D3DXMATRIX * TransMat, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos)
{
	D3DXMatrixTranslation(TransMat, TransPos->x*ScalPos->x, TransPos->y*ScalPos->y, TransPos->z*ScalPos->z);
}

D3DXMATRIX Judg::GetMatY(const D3DXMATRIX * MatA, const D3DXMATRIX * MatB)
{
	D3DXMATRIX Tmp;
	Tmp = *MatB;
	Tmp = *MatA*Tmp;
	return Tmp;
}

D3DXVECTOR3 Judg::GetVecVec(const D3DXVECTOR3 * VecA, const D3DXVECTOR3 * VecB)
{
	D3DXVECTOR3 A = *VecA,B=*VecB,Vec;
	Vec.x = A.x*B.x;
	Vec.y = A.y*B.y;
	Vec.z = A.z*B.z;
	return Vec;
}

D3DXVECTOR3 Judg::GetVecVec_S(const D3DXVECTOR3 * VecA, const D3DXVECTOR3 * VecB)
{
	D3DXVECTOR3 A = *VecA, B = *VecB, Vec;
	Vec.x = A.x/B.x;
	Vec.y = A.y/B.y;
	Vec.z = A.z/B.z;
	return Vec;
}

BASE3D Judg::InitGunParts(const Object3DGun * Init)
{
	BASE3D Base;
	Base.TraPos = Init->TransPos;
	setTransMat(&Base.Trans, &Base.TraPos);

	Base.ScaPos = Init->ScalPos;
	setScalingMat(&Base.Scal, &Base.ScaPos);

	Base.DrawFlg = Init->DrawFlg;

	Base.AngX = Init->AngX;
	D3DXMatrixRotationX(&Base.RotX,D3DXToRadian((float)Base.AngX));

	Base.AngY = Init->AngY;
	D3DXMatrixRotationY(&Base.RotY, D3DXToRadian((float)Base.AngY));

	Base.AngZ = Init->AngZ;
	D3DXMatrixRotationZ(&Base.RotZ, D3DXToRadian((float)Base.AngZ));

	return Base;
}

Object3DGun Judg::InitSetPartsData(const float AngX, const float AngY, const float AngZ, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos, const bool DrawFlg)
{
	Object3DGun o;
	o.AngX=AngX;
	o.AngY = AngY;
	o.AngZ = AngZ;
	o.TransPos = *TransPos;
	o.ScalPos = *ScalPos;
	o.DrawFlg = DrawFlg;
	return o;
}

S_GUN_DRAW_NO Judg::GetInitGUNDRAWNOS(const int GunNo, const int BulletNo, const int MuzFlaNo, const int LaserNo)
{
	S_GUN_DRAW_NO g;
	g.GunNo = GunNo;
	g.BulletNo = BulletNo;
	g.MuzFlaNo = MuzFlaNo;
	g.LaserNo = LaserNo;
	return g;
}

S_Random Judg::GetInitRand(const int x, const int y, const int z)
{
	S_Random r;
	r.x = x;
	r.y = y;
	r.z = z;
	return r;
}

D3DXMATRIX Judg::Get_IdenMat(void)
{
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	return IdenMat;
}

D3DXMATRIX Judg::Get_Mat_Init(void)
{
	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0.0f, 0.0f, 0.0f);
	return TmpMat;
}

bool Judg::Hit_No(const unsigned int * No, const unsigned int * NoNum)
{
	if (*No < 0)return false;
	if (*No >= *NoNum)return false;
	return true;
}

D3DXMATRIX Judg::Set_2DMat(const D3DXVECTOR3 * Pos)
{
	D3DXMATRIX Mat;
	D3DXMatrixTranslation(&Mat, Pos->x, Pos->y, NULL);
	return Mat;
}

D3DXVECTOR3 Judg::Get_Size3D(const float * Size)
{
	D3DXVECTOR3 Scal = D3DXVECTOR3(*Size, *Size, *Size);
	return Scal;
}

void Judg::Get_Size3D(D3DXVECTOR3 * Pos, const float * Size)
{
	*Pos = D3DXVECTOR3(*Size, *Size, *Size);
}

D3DXVECTOR3 Judg::Get_Size2D(const float * Size)
{
	D3DXVECTOR3 Scal = D3DXVECTOR3(*Size, *Size, 0.0f);
	return Scal;
}

D3DXVECTOR3 Judg::GetRayHitPos(const D3DXVECTOR3 * RayPos, const D3DXVECTOR3 * RayVec, const float * RayDis)
{
	D3DXVECTOR3 RayHitPos = (*RayPos) + (*RayVec)*(*RayDis);
	return RayHitPos;
}

void Judg::Set_Vec3_Vec2(D3DXVECTOR3 * Vec3, const D3DXVECTOR2 * Vec2)
{
	Vec3->x += Vec2->x;
	Vec3->y += Vec2->y;
}

void Judg::Change_Plus(float * f)
{
	if (*f < 0.0f)*f *= -1.0f;
}

void Judg::Change_Plus(D3DXVECTOR3 * Vec)
{
	Change_Plus(&Vec->x);
	Change_Plus(&Vec->y);
	Change_Plus(&Vec->z);
}

void Judg::Judg_BigNum(float * f_A, const float * f_B)
{
	if (*f_A < *f_B)*f_A = *f_B;
}

void Judg::Judg_BigNum(D3DXVECTOR3 * Vec_A, const D3DXVECTOR3 * Vec_B)
{
	Judg_BigNum(&Vec_A->x, &Vec_B->x);
	Judg_BigNum(&Vec_A->y, &Vec_B->y);
	Judg_BigNum(&Vec_A->z, &Vec_B->z);
}

D3DXVECTOR3 Judg::Get_RadiusVec(const D3DXVECTOR3 * Vec_A, const D3DXVECTOR3 * Vec_B)
{
	D3DXVECTOR3 v[] = { *Vec_A,*Vec_B };

	//マイナスをプラスに変換
	for (int i = 0; i < 2; i++) {
		Change_Plus(&v[i]);
	}

	//大きさ判定
	Judg_BigNum(&v[0], &v[1]);

	return v[0];
}

void Judg::Get_Draw_Radius(float * Radius, const D3DXVECTOR3 * Vec_Big, const D3DXVECTOR3 * Vec_Small, const D3DXVECTOR3 * Scal_Pos)
{
	D3DXVECTOR3 Vec_A = GetVecVec(Vec_Big, Scal_Pos),
		Vec_B = GetVecVec(Vec_Small, Scal_Pos);

	D3DXVECTOR3 Vec = Get_RadiusVec(&Vec_A, &Vec_B);

	//半径の取得
	*Radius = D3DXVec3Length(&Vec);

	//半径をプラスに変換
	Change_Plus(Radius);

	return;
}

bool Judg::Judg_PlusNum(const float * Num)
{
	if (*Num > 0.0f)return true;

	return false;
}

void Judg::Judg_Data_Num(int * Now_Num, const int * Max_Num)
{
	if (*Now_Num < 0)*Now_Num = 0;
	if (*Now_Num >= *Max_Num)*Now_Num = *Max_Num - 1;
}

int Judg::Judg_Data_Num2(const int * Now_Num, const int * Max_Num)
{
	if (*Now_Num < 0)return 0;

	if (*Now_Num >= *Max_Num)return *Max_Num - 1;

	return *Now_Num;
}

void Judg::Get_Frustum_NormalVec(S_Frustum_Vec * Data, const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport, const D3DXVECTOR3 * CameraPos)
{
	// カメラの位置取得
	Data->cameraPos = *CameraPos;

	// 視錐台の平面の法線ベクトル計算
	float x1 = (float)Viewport->X;
	float y1 = (float)Viewport->Y;
	float x2 = (float)Viewport->X + (float)Viewport->Width;
	float y2 = (float)Viewport->Y + (float)Viewport->Height;
	D3DXVECTOR3 Near[4];
	D3DXVECTOR3 Far[4];
	Near[0] = D3DXVECTOR3(x1, y1, 0);
	Near[1] = D3DXVECTOR3(x2, y1, 0);
	Near[2] = D3DXVECTOR3(x1, y2, 0);
	Near[3] = D3DXVECTOR3(x2, y2, 0);
	Far[0] = D3DXVECTOR3(x1, y1, 1);
	Far[1] = D3DXVECTOR3(x2, y1, 1);
	Far[2] = D3DXVECTOR3(x1, y2, 1);
	Far[3] = D3DXVECTOR3(x2, y2, 1);

	// 視錐台の８点の計算
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Unproject(&Near[i], &Near[i], Viewport, mProj, mView,
			&world);
		D3DXVec3Unproject(&Far[i], &Far[i], Viewport, mProj, mView,
			&world);
	}

	// 平面の3点から法線の計算
	D3DXVECTOR3 tmp1, tmp2;

	// 左
	tmp1 = Near[2] - Near[0];
	tmp2 = Far[0] - Near[0];
	D3DXVec3Cross(&Data->nl, &tmp1, &tmp2);
	D3DXVec3Normalize(&Data->nl, &Data->nl);

	// 右
	tmp1 = Near[3] - Near[1];
	tmp2 = Far[1] - Near[1];
	D3DXVec3Cross(&Data->nr, &tmp1, &tmp2);
	D3DXVec3Normalize(&Data->nr, &Data->nr);
	Data->nr *= -1.0f;

	// 上
	tmp1 = Near[3] - Near[2];
	tmp2 = Far[2] - Near[2];
	D3DXVec3Cross(&Data->nt, &tmp1, &tmp2);
	D3DXVec3Normalize(&Data->nt, &Data->nt);

	// 下
	tmp1 = Far[0] - Near[0];
	tmp2 = Near[1] - Near[0];
	D3DXVec3Cross(&Data->nb, &tmp1, &tmp2);
	D3DXVec3Normalize(&Data->nb, &Data->nb);
}

bool Judg::Judg_Frustum(const S_Frustum_Vec * Data, const D3DXVECTOR3 * Pos, const float * Radius)
{
	D3DXVECTOR3 pos = *Pos - Data->cameraPos;

	// 上下左右との比較(Near,Farは省略) normal ・ center > radius
	if ((Judg_Plane_Rad(&Data->nt, &pos, Radius)) || (Judg_Plane_Rad(&Data->nb, &pos, Radius))
		|| (Judg_Plane_Rad(&Data->nl, &pos, Radius)) || (Judg_Plane_Rad(&Data->nr, &pos, Radius))) {
		return false;
	}
	
	return true;
}

bool Judg::colCapsuleCapsule(const S_Capsule * c1, const S_Capsule * c2, float * d)
{
	D3DXVECTOR3 p1, p2;
	float t1, t2;
	*d = calcSegmentSegmentDist(&c1->l, &c2->l, &p1, &p2, &t1, &t2);
	if (*d <= c1->r + c2->r)return true;
	return false;
}

bool Judg::colCapsuleCapsuleDis(const S_Capsule * c1, const S_Capsule * c2, float * d)
{
	D3DXVECTOR3 p1, p2;
	float t1, t2;
	*d = calcSegmentSegmentDist(&c1->l, &c2->l, &p1, &p2, &t1, &t2);
	if (*d <= c1->r + c2->r) {
		*d = c1->r + c2->r - *d;
		return true;
	}
	return false;
}

bool Judg::colCapsuleCapsule(const S_Capsule * c1, const S_Capsule * c2, float * d, int * hitNum)
{
	float Dis = 0.0f;
	if (colCapsuleCapsuleDis(c1, c2, &Dis))
	{
		if (*hitNum <= 0)
		{
			*hitNum = 1;
			*d = Dis;
			return true;
		}

		*hitNum += 1;

		if (Dis > *d) 
		{
			*d = Dis;
			return true;
		}
	}

	return false;
}

bool Judg::Judg_Plane_Rad(const D3DXVECTOR3 * Vec, const D3DXVECTOR3* Pos, const float * Radius)
{
	if (Vec->x*Pos->x + Vec->y*Pos->y + Vec->z*Pos->z > * Radius)return true;
	return false;
}

float Judg::calcPointLineDist(const D3DXVECTOR3 * p, const S_Line *l, D3DXVECTOR3 * h, float *t)
{
	float lenSqV = D3DXVec3LengthSq(&l->v);
	*t = 0.0f;
	D3DXVECTOR3 v1 = *p - l->s;
	if (lenSqV > 0.0f)*t = D3DXVec3Dot(&l->v, &v1) / lenSqV;

	*h = getPoint(l, t);
	v1 = *h - *p;
	float len= D3DXVec3Length(&v1);
	return len;
}

bool Judg::isSharpAngle(const D3DXVECTOR3 * p1, const D3DXVECTOR3 * p2, const D3DXVECTOR3 * p3)
{
	D3DXVECTOR3 v1 = *p1 - *p2, v2 = *p3 - *p2;
	if (D3DXVec3Dot(&v1, &v2) >= 0.0f)return true;
	return false;
}

float Judg::calcPointSegmentDist(const D3DXVECTOR3 * p, const S_Line *l, D3DXVECTOR3 * h, float *t)
{
	// 垂線の長さ、垂線の足の座標及びtを算出
	float len = calcPointLineDist(p, l, h,t);

	if (isSharpAngle(p, &l->s, &l->e) == false) 
	{
		// 始点側の外側
		*h = l->s;
		D3DXVECTOR3 v = l->s - *p;
		len = D3DXVec3Length(&v);
		return len;
	}
	else {
		if (isSharpAngle(p, &l->e, &l->s) == false) 
		{
			// 終点側の外側
			*h = l->e;
			D3DXVECTOR3 v = l->e - *p;
			len = D3DXVec3Length(&v);
			return len;
		}
	}

	return len;
}

bool Judg::isParallel(const D3DXVECTOR3 * v1, const D3DXVECTOR3 * v2)
{
	D3DXVECTOR3 v;
	D3DXVec3Cross(&v, v1, v2);
	float d = D3DXVec3LengthSq(&v);
	// 誤差範囲内なら平行と判定
	float f = 0.000001f;
	if ((-f < d) && (d < f))return true;
	return false;
}

D3DXVECTOR3 Judg::getPoint(const D3DXVECTOR3 * p, const D3DXVECTOR3 * v, const float * t)
{
	D3DXVECTOR3 pos = (*p) + (*t)*(*v);
	return pos;
}

D3DXVECTOR3 Judg::getPoint(const S_Line * l, const float * t)
{
	D3DXVECTOR3 pos = (l->s) + (*t)*(l->v);
	return pos;
}

float Judg::calcLineLineDist(const S_Line * l1, const S_Line * l2, D3DXVECTOR3 * p1, D3DXVECTOR3 * p2, float * t1, float * t2)
{
	// 2直線が平行？
	if (isParallel(&l1->v, &l2->v) == true) {

		// 点P11と直線L2の最短距離の問題に帰着
		float len = calcPointLineDist(&l1->s, l2, p2, t2);
		*p1 = l1->s;
		*t1 = 0.0f;

		return len;
	}

	// 2直線はねじれ関係
	float DV1V2 = D3DXVec3Dot(&l1->v, &l2->v);
	float DV1V1 = D3DXVec3LengthSq(&l1->v);
	float DV2V2 = D3DXVec3LengthSq(&l2->v);
	D3DXVECTOR3 P21P11 = l1->s - l2->s;
	*t1 = (DV1V2 * D3DXVec3Dot(&l2->v, &P21P11) - DV2V2 * D3DXVec3Dot(&l1->v, &P21P11)) / (DV1V1 * DV2V2 - DV1V2 * DV1V2);
	*p1 = getPoint(l1, t1);
	D3DXVECTOR3 vec = *p1 - l2->s;
	*t2 = D3DXVec3Dot(&l2->v, &vec) / DV2V2;
	*p2 = getPoint(l2, t2);

	vec = *p2 - *p1;
	float len = D3DXVec3Length(&vec);
	return len;
}

void Judg::clamp01(float * v)
{
	if (*v < 0.0f)
	{
		*v = 0.0f;
	}
	else
	{
		if (*v > 1.0f)
		{
			*v = 1.0f;
		}
	}
}

float Judg::calcSegmentSegmentDist(const S_Line * l1, const S_Line * l2, D3DXVECTOR3 * p1, D3DXVECTOR3 * p2, float * t1, float * t2)
{
	float _OX_EPSILON_ = 0.000001f;

	// S1が縮退している？
	if (D3DXVec3LengthSq(&l1->v) < _OX_EPSILON_) {
		// S2も縮退？
		if (D3DXVec3LengthSq(&l2->v) < _OX_EPSILON_) {
			// 点と点の距離の問題に帰着
			D3DXVECTOR3 v = l2->s - l1->s;
			float len = D3DXVec3Length(&v);
			*p1 = l1->s;
			*p2 = l2->s;
			*t1 = *t2 = 0.0f;
			return len;
		}
		else {
			// S1の始点とS2の最短問題に帰着
			float len = calcPointSegmentDist(&l1->s, l2, p2, t2);
			*p1 = l1->s;
			*t1 = 0.0f;
			clamp01(t2);
			return len;
		}
	}
	else
	{
		// S2が縮退している？
		if (D3DXVec3LengthSq(&l2->v) < _OX_EPSILON_) {
			// S2の始点とS1の最短問題に帰着
			float len = calcPointSegmentDist(&l2->s, l1, p1, t1);
			*p2 = l2->s;
			clamp01(t1);
			*t2 = 0.0f;
			return len;
		}
	}

	/* 線分同士 */

	// 2線分が平行だったら垂線の端点の一つをP1に仮決定
	if (isParallel(&l1->v, &l2->v) == true) {
		*t1 = 0.0f;
		*p1 = l1->s;
		float len = calcPointSegmentDist(&l1->s, l2, p2, t2);
		if ((0.0f <= *t2) && (*t2 <= 1.0f))return len;
	}
	else {
		// 線分はねじれの関係
		// 2直線間の最短距離を求めて仮のt1,t2を求める
		float len = calcLineLineDist(l1, l2, p1, p2, t1, t2);
		if ((0.0f <= *t1) && (*t1 <= 1.0f) &&
			(0.0f <= *t2) && (*t2 <= 1.0f)) return len;
	}

	// 垂線の足が外にある事が判明
	// S1側のt1を0～1の間にクランプして垂線を降ろす
	clamp01(t1);
	*p1 = getPoint(l1, t1);
	float len = calcPointSegmentDist(p1, l2, p2, t2);
	if ((0.0f <= *t2) && (*t2 <= 1.0f))return len;

	// S2側が外だったのでS2側をクランプ、S1に垂線を降ろす
	clamp01(t2);
	*p2 = getPoint(l2, t2);
	len = calcPointSegmentDist(p2, l1, p1, t1);
	if ((0.0f <= *t1) && (*t1 <= 1.0f))return len;

	// 双方の端点が最短と判明
	clamp01(t1);
	*p1 = getPoint(l1, t1);
	len= D3DXVec3Length(&(*p2 - *p1));
	return len;
}

D3DXVECTOR3 Judg::VecPos(D3DXMATRIX MatA, D3DXVECTOR3 VecA)
{
	D3DXMATRIX TransMat;
	D3DXVECTOR3 Pos;
	SetPosM(&Pos, &MatA);
	Pos = VecA - Pos;
	return Pos;
}
