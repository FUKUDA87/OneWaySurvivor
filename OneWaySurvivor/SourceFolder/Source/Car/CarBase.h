#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include<vector>
#include"../Ground/Ground_Object.h"
#include"../Car/Data/Draw3DManager/CarMeshManager.h"
#include"../GameSource/CharaBase.h"
#include"../GameSource/Const.h"
#include"../GameSource/StructManager.h"

class C_CarBase:public C_CharaBase 
{
public:
	C_CarBase();

	//�ԑ̍s��n��
	D3DXMATRIX GetMatCar(void) { return Car.Base.Mat; }

	//�ԑ̍s�����
	void SetMatCar(const D3DXMATRIX *Mat) { Car.Base.Mat = *Mat; }

	//������n�ʂ�No����
	void SetGroNum(const unsigned int *GroundNo) { Car.Con.GroNum = *GroundNo; }

	//�O�i�A�b�v�f�[�g
	virtual bool UpdateCarFM(std::vector<C_Ground_Object*>ground);

	//�ړ��̏��n��
	CONSTITUTION GetCon(void) { return Car.Con; }

	//����Hp����
	virtual bool SetHP(int Damage);
	//����Hp����(�ǂƒe�̋�ʕt)
	virtual bool SetHP(int Damage, bool WallFlg);

	//�Ԃ̑���Flg�n��
	bool GetFlgCar(void) { return Car.Base.Flg; }

	// ���ړ��̔��f
	void SetSideTransMat(const float *MoveX);

	//�ԏ��
	CHARAData GetData(void);

	//�ړ��̏���n��
	QuaForMove GetQuaForMove(void);

	//player��TransMat�n��
	D3DXMATRIX GetTransMatCar(void) { return Car.Base.Trans; }

	//�O�i����p�֐�-----------------------------------------------

	//�O�i����p�̈ړ���Mat����
	void SetForMoveEndMat(const D3DXMATRIX *Mat) { ForMoveEndMat = *Mat; }

	//�O�i����p�̈ړ��x�N�g������
	void SetForMoveVec(const D3DXVECTOR3 *Vec) { ForMoveVec = *Vec; }
	
	//�ړ��x�N�g���̒�������
	void SetQuaVecSize(const float *size) { CarFM.SpeedMulJudg = *size; }

	//�O�i����p�̈ړ��x�N�g���n��
	D3DXVECTOR3 GetForMoveVec(void) { return ForMoveVec; }

	//�O�i����p�̈ړ���Mat�n��
	D3DXMATRIX GetForMoveEndMat(void) { return ForMoveEndMat; }

	//���S�m�F(true�Ŏ�)
	bool Dead(void);

	//�Փ˔��肷�邱�Ƃ�������t���O�̓n��
	bool Get_CollisionJudg_TrueFlg(void) { return M_CollisionJudg_TrueFlg; }

	//�����蔻��̔��a�n��
	float GetBodRadCar(void) { return Car.Base.BodRad; }

	//�g��n��
	D3DXVECTOR3 GetScalPosCar(void) { return Car.Base.ScaPos; }

	//�Փ˔���̏�Ԃ̓n��
	int Get_JudgeType(void) { return M_JudgeType; }

	//�O�̎Ԃ̈ʒu�̃Z�b�g
	void SetCarMoveMat(void) { PlaMovMat = Car.Base.Trans*Car.Con.JudgMat; }

	//�X�s�[�h����
	void SetSpeedCar(const D3DXVECTOR3 *spe) { Car.Con.Speed = *spe; }

	// ������
	bool BallJudgCar(const D3DXVECTOR3 *Pos, const float *Radius);
	bool BallJudgCar(bool * JudgFlg, float * SmallDis, const D3DXMATRIX * EndMat, const float * Radius);

	//����E����ł���܂ł̎��Ԃ̓n��
	int Get_Move_Stop_Time(void) { return MMove_Stop_Time; }

	//����E����ł���܂ł̎��Ԃ̓���
	void Set_Move_Stop_Time(const int *Time, const int *Speed);

	//�蓮�Ǝ����̑����������N���X
	S_GUN_UPDATE_DATA Get_Gun_Update_Data(void) { return M_S_Gun_Update_Data; }

	// ���C����
	virtual void RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad);

	// �J�v�Z������
	virtual bool capsuleJudg(float *sd, int *hitNum, const S_Capsule *c,const bool *ForMoveJudgFlg);

	// �J�v�Z���擾
	S_Capsule GetCapsule(const bool *EndMatFlg);

	D3DXMATRIX getSparkInitMat(const float *MoveVecX,const bool *wallHitFlg);
protected:
	//�Ԃ̃f�[�^
	BODYDATA BodyData;

	//�Ԃ̃��f������
	void SetMeshCar(int MeshNo);

	//�Ԃ̏��
	CHARA3D Car;

	QuaForMove CarFM;

	D3DXMATRIX PlaMovMat;//player�̈ړ��O��Mat

	//�o���b�g�p
	BULLETRAYJUDG brj;

	Judg judg;

	//�蓮�Ǝ����̑����������N���X
	S_GUN_UPDATE_DATA M_S_Gun_Update_Data;

	S_Capsule capsule;  // �J�v�Z��

	//�Ԃ̑����
	int M_Driver;

	//�e�̏��̍X�V
	void Update_Gun_Data(void);

	//����E����ł���܂ł̎��Ԃ����炷�X�V�̏���
	void Update_Move_Stop_Time(void);

	//�e�̓����̒�~����
	bool Get_Stop_Flg(void);

	//�Փ˔���̏�Ԃ̃Z�b�g
	void Set_JudgeType(const int *Type) { M_JudgeType = *Type; }

	// ���C����
	bool RayJudgCar(const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray, BULLETJUDGDATA * BJD);

	//�A�b�v�f�[�g
	virtual bool UpdateCar(void);

	//3D�\��
	virtual void Draw3DCar(void);

	//�p�[�c�̈ʒu����
	virtual void SetParts(std::vector<C_Ground_Object*>ground);
	
	//�Ԃ̑���Flg����
	void SetFlgCar(const bool *Flg) { Car.Base.Flg = *Flg; }

	//player��TransMat����
	void SetTransMatCar(const D3DXMATRIX *TransMat) { Car.Base.Trans = *TransMat; }

	//�X�s�[�h����
	void SetNowSpeedCar(int spe) { Car.Con.NowSpeed = spe; }

	//�e�o��������
	void SetBPos(D3DXVECTOR3 RayPos, bool RayJudgFlg);

	//���G�A�b�v�f�[�g
	bool UpdateCountM(void);

	//���쐬�ɕK�v�ȏ��̎擾�ƃA�b�v�f�[�g
	virtual void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport) {};

	//�ړ��x�N�g���n��
	D3DXVECTOR3 GetMoveVec(void) { return brj.MoveVec; }

	//�J�����̍s��̃Z�b�g
	virtual void Set_CameraMat(const D3DXMATRIX *CameraMat) {
		M_S_Gun_Update_Data.CameraMat = *CameraMat;
	}

	//�Ԃ̑���҂̓n��
	int Get_DriverNo(void) { return M_Driver; }

	/*�Փ˔���̏�Ԃ̊֐�*/

	//�Փ˔��肷�邱�Ƃ�������t���O�̃Z�b�g
	void Set_CollisionJudg_TrueFlg(const bool *Flg) { M_CollisionJudg_TrueFlg = *Flg; }

	// ��
	int GetConstCar(void);
private:

	//�Փ˔���̏��
	int M_JudgeType;

	//����E����ł���܂ł̎���
	int MMove_Stop_Time;

	//�Փ˔��肷�邱�Ƃ�������t���O
	bool M_CollisionJudg_TrueFlg;

	//�O�i�N�H�[�^�j�I���p
	D3DXMATRIX ForMoveEndMat;//�O�i��������Mat
	D3DXVECTOR3 ForMoveVec;//�ړ��O����ړ����Vec
	QuaForMove Q;//�O�i����p�N�H�[�^�j�I��

	//���G�^�C��
	int CountMNum,CountMStart;

	// �J�v�Z��������
	void capsuleInit(const bool *EndMatFlg);

	//�Ԃ̕\���s��n��
	virtual D3DXMATRIX GetDrawMatCar(void) {
		return judg.GetDrawMat(&Car.Base.Mat, &Car.Base.Scal, &Car.Base.ScaPos);
	}
};