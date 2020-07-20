#pragma once
#include<d3dx9.h>
#include"Struct.h"

#ifndef Judgm_H
#define Judgm_H

extern LPDIRECT3DDEVICE9 lpD3DDevice;


class Judg {
public:
	//��������
	bool BallJudg(const D3DXVECTOR3 *PosA, const D3DXVECTOR3 *PosB,const float *Radius);
	bool BallJudg(float * SmallDis, const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB, const float * Radius, const bool *Flg);
	//��������+���Ƌ�
	bool ball(D3DXMATRIX mat1, D3DXMATRIX mat2, float rad, D3DXMATRIX *Trans1, D3DXMATRIX *Trans2);
	//��������+�����擾
	float BallJudg(const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB);

	//�o������ʒu�ɔ��Ȃ��l�ɂ��锻��
	bool Pop_BallJudg(const D3DXVECTOR3 *PosA, const D3DXVECTOR3 *PosB, const float *Radius);

	//Hp�̏���
	bool HPj(int *NowHp, int *NowMaxHp);

	/*���C����*/

	//�|���S���Ƀ��C����
	bool RayJudg_Polygon(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD, float *Dis);

	//�|���S���Ƀ��C����(+�s�񂩂璸�_�v�Z)
	bool RayJudg_Polygon(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec, const D3DXMATRIX *Polygon_Mat,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD, float *Dis);

	//�|���S���Ƀ��C����(+���C�����ޔ���)
	bool RayJudg_Polygon(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec, const D3DXMATRIX *Polygon_Mat,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD,
		float *Dis, const bool *Judg_Type_IdenMat);

	//�|���S���Ƀ��C����+���C������������������
	bool RayJudg_Polygon_SmallDis(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec, const D3DXMATRIX *Polygon_Mat,
		const D3DXVECTOR3 *vA,const D3DXVECTOR3 *vB,const D3DXVECTOR3 *vC,const D3DXVECTOR3 *vD, float *Small_Dis);

	//�|���S�Ƀ��C����+���C������������������(+�s�񂩂璸�_�v�Z)
	bool RayJudg_Polygon_SmallDis(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD, float *Small_Dis);

	//Mesh�Ƀ��C����
	bool RayJudg_Mesh(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXMATRIX *Draw_Mat, const LPD3DXMESH Mesh, float *Dis);

	//Mesh�Ƀ��C����(���������|���S����)
	int RayJudg_Mesh_PolNum(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXMATRIX *Draw_Mat, const LPD3DXMESH Mesh, float *Dis);

	//Mesh�Ƀ��C����+���C������������������
	bool RayJudg_Mesh_SmallDis(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXMATRIX *Draw_Mat, const LPD3DXMESH Mesh, float *Small_Dis);

	/**/

	//3D����2D�̍��W�擾
	void Pos2D(D3DXVECTOR3 *Pos_2D,const D3DXVECTOR3 *Pos3D,const D3DXMATRIX *mProj,const D3DXMATRIX *mView,const D3DVIEWPORT9 *Viewport);
	//3D����2D�̍��W�擾+player��enemy�̋t�ʒu�쐬
	void Pos2DPE(D3DXVECTOR3 *Pos_2D,const D3DXMATRIX *eMat,const D3DXMATRIX *pMat, const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport);
	//Ang�v�Z
	double Ang(D3DXVECTOR3 pla, D3DXVECTOR3 tar, D3DXVECTOR3 vec);
	
	//�O�ϓ���
	bool CroDot(D3DXMATRIX mat, D3DXMATRIX *rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec, double *Ang,double ang, bool angF);
	//tragetX��]�p(�~�T�C����])
	bool TarRotX(D3DXMATRIX mat, D3DXMATRIX * rotX, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec);
	//tragetY��]�p(�J�c�I��])
	bool TarRotY(D3DXMATRIX mat,D3DXMATRIX *rotY,  D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec);
	//tragetEndMat�쐬
	bool TarEndMat(D3DXMATRIX *mat,D3DXMATRIX TransMat, D3DXMATRIX * RotXMat, D3DXMATRIX *RotYMat, D3DXVECTOR3 TargetPos, D3DXVECTOR3 FrontVec);

	//�s������W�ɕϊ�
	D3DXVECTOR3 SetPosM(const D3DXMATRIX *Mat);
	D3DXVECTOR2 SetPos2DM(const D3DXMATRIX *Mat);
	void SetPosM(D3DXVECTOR3 *Pos, const D3DXMATRIX *Mat);

	//���W���s��ɕϊ�
	D3DXMATRIX SetMatP(const D3DXVECTOR3 *Pos);
	void SetMatP(D3DXMATRIX *Mat,const D3DXVECTOR3 *Pos);

	//�ړ��s��̃Z�b�g
	void setTransMat(D3DXMATRIX *TransMat, const D3DXVECTOR3 *TransPos);
	void setTransMat(D3DXMATRIX *TransMat, const D3DXVECTOR2 *TransPos);
	D3DXMATRIX getTransMat(const D3DXVECTOR3 *TransPos);
	D3DXMATRIX getTransMat(const D3DXVECTOR2 *TransPos);

	//�N�H�[�^�j�I��==============================================================================================
	//�A�j���[�V����
	bool AnimeProc(D3DXMATRIX *NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float AnimeFrame);
	void AnimeQua(D3DXMATRIX *NowMat,const D3DXMATRIX *StartMat,const D3DXMATRIX *EndMat,const float *AnimeFrame);
	bool AnimeProc(D3DXVECTOR3 *NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float AnimeFrame);
	//AnimeFrame+=
	bool AnimeFrameInc(float *AnimeFrame, float up, bool upFlg);
	bool AnimeFrameInc(float *AnimeFrame,const float *up,const bool *FrameMoveFlg);
	//�A�j���[�V����+AnimeFrame+=
	bool Quaternion(D3DXMATRIX *NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float *AnimeFrame, float up, bool upFlg);
	bool Quaternion(D3DXVECTOR3 *NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float *AnimeFrame, float up, bool upFlg);
	bool Quaternion(D3DXVECTOR2 *NowPos, D3DXVECTOR2 StartPos, D3DXVECTOR2 EndPos, float *AnimeFrame, float up, bool upFlg);
	//���C�����Dis��Pos�ϊ�
	D3DXVECTOR3 DisPos(D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, float Dis);
	//�r���{�[�h
	D3DXVECTOR3 Billboard(const D3DXVECTOR3 *OldPos, const D3DXVECTOR3 *NowPos, const D3DXVECTOR3 *camPos, const float *Size);
	//�r���{�[�h�{�|���Ή�
	D3DXVECTOR3 Billboard(const D3DXVECTOR3 *OldPos, const D3DXVECTOR3 *NowPos, const D3DXVECTOR3 *CameraPos, const float *Size, const bool *Reverse);
	//���ƃ��C2D
	bool LineLine(const D3DXVECTOR2 PosA, const D3DXVECTOR2 VecA, const D3DXVECTOR2 PosB, const D3DXVECTOR2 VecB, float *Dis);
	//�摜�̔����T�C�Y
	D3DXVECTOR2 HalfSize(const D3DXVECTOR3 sPos, const int Width, const int Height);
	//2D�̉摜�̘g�v�Z
	bool PlaneP(RECT *rc, const D3DXVECTOR2 *Pos, const D3DXVECTOR2 *scalSize, const int *Width, const int *Height);
	//2D�摜�N���b�N(�l�p�`)
	bool PlaneCri(const D3DXVECTOR2 *Pos, const D3DXVECTOR2 *scalSize, const int *Width, const int *Height);
	bool PlaneCri(const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *scalSize, const int *Width, const int *Height);
	//�}�E�X�ʒu
	POINT GetPoint(void);
	//rayray3D
	bool LineLine3D(D3DXVECTOR3 *GetPos, D3DXVECTOR3 PosA1, D3DXVECTOR3 PosA2, D3DXVECTOR3 PosB1, D3DXVECTOR3 PosB2);
	//vectorPos
	D3DXVECTOR3 VecPos(D3DXMATRIX MatA, D3DXVECTOR3 PosB);
	//**Mat����
	bool SetppMat(D3DXMATRIX *Mat, D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, D3DXVECTOR3 PosC, int RailNum, bool bc);
	//Vec=MatB-MatA
	bool MatMatVec(D3DXVECTOR3*Vec, D3DXMATRIX MatA, D3DXMATRIX MatB);
	D3DXVECTOR3 MatMatVec(D3DXMATRIX MatA, D3DXMATRIX MatB);
	bool VecMatIn(D3DXMATRIX *Mat,const D3DXVECTOR3 *Vec);
	//Speed�N�H�[�^�j�I���ϐ�
	bool SetFloatQ(float *f);
	bool SetFloatQ(D3DXVECTOR3 *Pos);
	float SlashFloat(float fA, float fB);

	// ��Βl
	void Ads(float *f);
	void Ads(D3DXVECTOR3 *p);

	// �傫����r
	bool Big(float *fa, const float *fb);
	bool Big(float *f, const float *fa, const float *fb);
	bool Big(D3DXVECTOR3 *p, const D3DXVECTOR3 *pa, const D3DXVECTOR3 *pb);
	bool Big(D3DXVECTOR3 *BigVec, const D3DXVECTOR3 *p);

	bool Small(float *fa, const float *fb);
	bool Small(D3DXVECTOR3 *SmallVec, const D3DXVECTOR3 *p);

	//���a�����߂�
	float GetRad(XFILE_B * MeshData);

	//���o�[�XFlg
	void ReverseFlg(bool *Flg);
	//���o�[�XFlg
	bool ReverseFlg2(const bool *Flg);
	int Reverse(const bool *Flg);

	//�X�P�C�����OMat����
	void setScalingMat(D3DXMATRIX *ScalMat, const D3DXVECTOR3 *Pos);
	void setScalingMat(D3DXMATRIX *ScalMat, const D3DXVECTOR2 *Pos);
	D3DXMATRIX getScalingMat(const D3DXVECTOR3 *Pos);
	D3DXMATRIX getScalingMat(const D3DXVECTOR2 *Pos);

	//RotX�̏�����
	void InitRotX(const D3DXMATRIX * Mat,D3DXMATRIX*RotX);
	//�N�H�[�^�j�I���\���̂̏������֐�
	QuaAnimeC InitQuaAnime(const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float *NowAnime, const float *AnimeFrame);
	//�������P
	void InitMatPos(D3DXMATRIX *Mat, D3DXVECTOR3 *TransPos, D3DXVECTOR3 *ScalPos);
	//�\���p�̍s��쐬
	D3DXMATRIX GetDrawMat(const D3DXMATRIX *Mat,D3DXMATRIX *ScalMat, const D3DXVECTOR3 *ScalPos);
	D3DXMATRIX GetDrawMat(const D3DXMATRIX *Mat,const D3DXVECTOR3 *ScalPos);
	//�������Q
	BASE3D GetInitBase3D(const D3DXVECTOR3 *InitPos, const D3DXVECTOR3 *TransPos, const D3DXVECTOR3 *ScalPos,
		const double * AngX, const  double * AngY, const  double * AngZ);

	//����p�̊g����܂߂��ړ��s��̍쐬
	D3DXMATRIX GetTransMatScal(const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* ScalPos);
	void Get_TransMatScal(D3DXMATRIX *TransMat,const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* ScalPos);

	//�s��̍���(MatA*MatB)
	D3DXMATRIX GetMatY(const D3DXMATRIX *MatA, const D3DXMATRIX *MatB);
	//�x�N�g���̊|���Z
	D3DXVECTOR3 GetVecVec(const D3DXVECTOR3 *VecA, const D3DXVECTOR3 *VecB);
	//�x�N�g���̊���Z
	D3DXVECTOR3 GetVecVec_S(const D3DXVECTOR3 *VecA, const D3DXVECTOR3 *VecB);
	//�ʒu�̏�����(Gun�o�[�W����)
	BASE3D InitGunParts(const Object3DGun* Init);
	//�ʒu�̏�����(Gun�o�[�W����)
	Object3DGun InitSetPartsData(const float AngX,const float AngY,const float AngZ,const D3DXVECTOR3 *TransPos, const D3DXVECTOR3 *ScalPos,const bool DrawFlg);
	//�������\����
	S_GUN_DRAW_NO GetInitGUNDRAWNOS(const int GunNo, const int BulletNo, const int MuzFlaNo, const int LaserNo);
	
	//�����̏�����
	S_Random GetInitRand(const int x, const int y, const int z);
	//�P�ʍs��n��
	D3DXMATRIX Get_IdenMat(void);
	//�������s��n��
	D3DXMATRIX Get_Mat_Init(void);
	//�����Ă����ԍ��̌���
	bool Hit_No(const unsigned int *No,const unsigned int *NoNum);
	//�QD�s���Vec3������
	D3DXMATRIX Set_2DMat(const D3DXVECTOR3 *Pos);
	//�T�C�Y���x�N�g���ϊ�
	D3DXVECTOR3 Get_Size3D(const float *Size);
	void Get_Size3D(D3DXVECTOR3 *Pos,const float *Size);
	D3DXVECTOR3 Get_Size2D(const float *Size);

	//���C�������������W�����߂�
	D3DXVECTOR3 GetRayHitPos(const D3DXVECTOR3 *RayPos, const D3DXVECTOR3* RayVec, const float *RayDis);

	//Vec3��Vec2�𑫂�
	void Set_Vec3_Vec2(D3DXVECTOR3 *Vec3, const D3DXVECTOR2 *Vec2);

	//�}�C�i�X���v���X�ɕϊ�
	void Change_Plus(float *f);
	void Change_Plus(D3DXVECTOR3 *Vec);

	//�傫������
	void Judg_BigNum(float *f_A, const float *f_B);
	void Judg_BigNum(D3DXVECTOR3 *Vec_A, const D3DXVECTOR3 *Vec_B);

	//���a�̃x�N�g�������߂鏈��
	D3DXVECTOR3 Get_RadiusVec(const D3DXVECTOR3 *Vec_A, const D3DXVECTOR3 *Vec_B);
	//���a�̃x�N�g�������߂��ۂɔ��a���v�Z����
	void Get_Draw_Radius(float *Radius,const D3DXVECTOR3 *Vec_Big, const D3DXVECTOR3 *Vec_Small, const D3DXVECTOR3 *Scal_Pos);

	//�[������̂Ȃ�ture��Ԃ�
	bool Judg_PlusNum(const float *Num);

	//�ԍ��̔���
	void Judg_Data_Num(int *Now_Num, const int *Max_Num);
	int Judg_Data_Num2(const int *Now_Num, const int *Max_Num);

	//������̖@���x�N�g���̌v�Z
	void Get_Frustum_NormalVec(S_Frustum_Vec *Data, const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport,const D3DXVECTOR3 *CameraPos);
	//������J�����O�̔���(������̒��ɂ���ꍇ�Atrue)
	bool Judg_Frustum(const S_Frustum_Vec *Data,const D3DXVECTOR3 *Pos, const float *Radius);

	// �J�v�Z�����m�̏Փ˔���
	bool colCapsuleCapsule(const S_Capsule *c1, const S_Capsule *c2, float *d);
	bool colCapsuleCapsuleDis(const S_Capsule *c1, const S_Capsule *c2, float *d);
	bool colCapsuleCapsule(const S_Capsule *c1, const S_Capsule *c2, float *d, int *hitNum);

	// �����v�Z
	float rate(const float *Base, const float *f) { return (*f) / (*Base); }
	float rate(const int *Base, const float *f) { return (*f) / (float)(*Base); }
private:

	//���ʂƔ��a�̔���
	bool Judg_Plane_Rad(const D3DXVECTOR3 *Vec, const D3DXVECTOR3 *Pos, const float *Radius);


	// �_�ƒ����̍ŒZ����
	float calcPointLineDist(const D3DXVECTOR3 *p, const S_Line *l, D3DXVECTOR3 *h,float *t);
	// �݊p����
	bool isSharpAngle(const D3DXVECTOR3 *p1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *p3);
	// �_�Ɛ����̍ŒZ����
	float calcPointSegmentDist(const D3DXVECTOR3 *p, const S_Line *l, D3DXVECTOR3 *h, float *t);
	// ���s�֌W
	bool isParallel(const D3DXVECTOR3 *v1, const D3DXVECTOR3 *v2);
	//  �x�N�g���Ɋ|���Z����W��
	D3DXVECTOR3 getPoint(const D3DXVECTOR3 *p, const D3DXVECTOR3 *v, const float *t);
	D3DXVECTOR3 getPoint(const S_Line *l, const float *t);
	// 2�����̍ŒZ����
	float calcLineLineDist(const S_Line *l1, const S_Line *l2, D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, float *t1, float *t2);
	// 0�`1�̊ԂɃN�����v
	void clamp01(float *v);
	// 2�����̍ŒZ����
	float calcSegmentSegmentDist(const S_Line *l1, const S_Line *l2, D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, float *t1, float *t2);
};

#endif // !Judgm_H

/*plus
#include"Judgment.h"

extern Judg *judg;
*/