#include"Calculation.h"

D3DXMATRIX Cal::CroDot(D3DXMATRIX *Mat, D3DXMATRIX tarMat, D3DXVECTOR3 FrontVec) {
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, Mat);
	D3DXVECTOR3 TargetPos;
	D3DXVec3TransformCoord(&TargetPos, &D3DXVECTOR3(tarMat._41, tarMat._42, tarMat._43), &InvMat);
	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	float Dot;
	Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
	if (Dot > 1)Dot = 1;
	if (Dot < -1)Dot = -1;
	double Ang;
	Ang = D3DXToDegree(acos(Dot));
	D3DXMATRIX TmpMat;
	D3DXMatrixRotationAxis(&TmpMat, &RotAxis, D3DXToRadian((float)Ang));
	*Mat=TmpMat * *Mat;
	return *Mat;
}
D3DXMATRIX Cal::CroDot(D3DXMATRIX *Mat, D3DXMATRIX tarMat, D3DXVECTOR3 FrontVec,float f) {
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, Mat);
	D3DXVECTOR3 TargetPos;
	D3DXVec3TransformCoord(&TargetPos, &D3DXVECTOR3(tarMat._41, tarMat._42, tarMat._43), &InvMat);
	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	float Dot;
	Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
	if (Dot > 1)Dot = 1;
	if (Dot < -1)Dot = -1;
	double Ang;
	Ang = D3DXToDegree(acos(Dot));
	if (Ang > f)Ang = f;
	D3DXMATRIX TmpMat;
	D3DXMatrixRotationAxis(&TmpMat, &RotAxis, D3DXToRadian((float)Ang));
	*Mat = TmpMat * *Mat;
	return *Mat;
}

//
double Cal::absd(double d) {
	if (d < 0.0) {
		d *= -1;
	}
	return d;
}
int Cal::absi(double d) {
	if (d < 0.0) {
		d *= -1;
	}
	int i;
	i = (int)d;
	return i;
}

//”Âƒ|ƒŠ‚Æü‚ÌŒvŽZ
bool Cal::BoaPolLei(D3DXMATRIX Mat, D3DXMATRIX eMat, D3DXMATRIX pMat, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXMATRIX point) {
	//–@ü‹‚ß‚é
	//–@ü‚Ž‚ÆVector1‚Æ‚Q
	D3DXVECTOR3 n,vv1,vv2;
	vv1 = v1 - v0;
	vv2 = v2 - v1;
	D3DXVec3Cross(&n, &vv1, &vv2);
	D3DXVec3Normalize(&n, &n);
	//ü‚Æ”Âƒ|ƒŠ‚ÌÕ“Ë”»’è
	D3DXVECTOR3 start=D3DXVECTOR3(Mat._41, Mat._42, Mat._43), 
	end=D3DXVECTOR3(eMat._41, eMat._42, eMat._43);
	//ƒ|ƒŠƒSƒ““_‚Mat‚©‚çMat‚ÆeMat‚ÉL‚Ñ‚éPS,PE‚Ìì¬
	D3DXVECTOR3 PS = D3DXVECTOR3(pMat._41 - start.x, pMat._42 - start.y, pMat._43 - start.z);
	D3DXVECTOR3 PE = D3DXVECTOR3(pMat._41 - end.x, pMat._42 - end.y, pMat._43 - end.z);

	double dot_PS = D3DXToDegree(acos(D3DXVec3Dot(&PS, &n)));
	double dot_PE = D3DXToDegree(acos(D3DXVec3Dot(&PE, &n)));
	if (dot_PS==0.0&&dot_PE==0.0) {
		return false;
	}
	else {
		if ((dot_PS >= 0.0&&dot_PE <= 0.0) ||
			(dot_PS <= 0.0&&dot_PE >= 0.0)) {

		}
		else {
			return false;
		}
	}

	D3DXVECTOR3 SE = D3DXVECTOR3(end.x - start.x, end.y - start.y, end.z - start.z);
	
	//
	//int i;
	float hiritu =(float)(absi(dot_PS) / (absi(dot_PS) + absi(dot_PE)));

	D3DXVECTOR3 Point = D3DXVECTOR3(start.x + (SE.x*hiritu), start.y + (SE.y*hiritu), start.z + (SE.z*hiritu));

	//ƒ|ƒŠƒSƒ“‚Æ“_‚Ì”»’è

	return true;
}