#include "CarBase.h"
#include"../MaterialManager/XfileManager.h"
#include"../GameSource/Motion.h"

extern XFileManager xfileManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern Motion motion;

void DrawMesh(XFILE *XFile, bool *Flg);


C_CarBase::C_CarBase()
{
	//������Flg�̏�����
	Car.Base.Flg = true;

	//�s��̏�����
	judg.InitMatPos(&Car.Base.Mat, &Car.Base.TraPos, &Car.Base.ScaPos);
	judg.setTransMat(&Car.Base.Trans, &Car.Base.TraPos);
	//���b�V���̏�����
	SetMeshCar(1);
	//�Ԃ̔���p

	//�o���b�g��񏉊���
	brj.JudgRayFlg = false;

	//�O�i�N�H�[�^�j�I���̏�����
	CarFM.AnimeFrame = 0.0f;
	CarFM.QuaInitFlg = false;
	CarFM.QuaMatInitFlg = false;
	CarFM.CurFlg = false;
	CarFM.SpeedMulJudg = 1.0f;
	CarFM.BodyHeight = 0.5f;

	//���G������
	CountMStart = 5;
	CountMNum = 0;

	//�Ԕ���
	SetDamageFlg(&Co_Damage_Yes);

	//���Ԃ̏�����
	MMove_Stop_Time = 0;

	//�Փ˔��肷�邱�Ƃ�������t���O�̏�����
	M_CollisionJudg_TrueFlg = true;

	//�Փ˔���̏�Ԃ̏�����
	M_JudgeType = Co_Judge_YES;


	//����̍\���̂̏�����
	M_S_Gun_Update_Data.NowPhase = 0;
}

bool C_CarBase::UpdateCar(void)
{
	return false;
}

bool C_CarBase::UpdateCarFM(std::vector<C_Ground_Object*> ground)
{
	if (Car.Con.NowSpeed <= 0)return true;

	//�O�i����
	CarFM.NowMat = Car.Base.Mat;
	motion.Formove(&CarFM, &Car.Con, ground);
	//�ԑ̂̕����𓾂邽�߂�Mat������
	Car.Con.JudgMat = CarFM.NowMat;
	Car.Base.Mat = Car.Base.Trans*CarFM.NowMat;
	return true;
}

void C_CarBase::Draw3DCar(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatCar());
		DrawMesh(&Car.Mesh.DrawMesh, &Body_DamageFlg);
	/*}
	else {
		DrawMesh(&Car.Con.DeadMesh, &Body_DamageFlg);
	}*/
}

void C_CarBase::SetParts(std::vector<C_Ground_Object*> ground)
{
}

bool C_CarBase::Dead(void)
{
	if (CharaBase.NowHp <= 0) {
		bool Flg = false;
		SetFlgCar(&Flg);
		return true;
	}
	return false;
}

bool C_CarBase::SetHP(int Damage)
{
	if (CountMNum > 0)return false;

	int NowHp = GetHp();

	if (HpDamage(&Damage) != true)return false;

	if (GetHp() < NowHp)Body_DamageFlg = true;
	//���G�̏�����
	CountMNum = CountMStart;

	return true;
}

bool C_CarBase::SetHP(int Damage, bool WallFlg)
{
	if (CountMNum > 0)return false;

	int NowHp = GetHp();
	
	if (HpDamage(&Damage) != true)return false;

	if (GetHp() < NowHp)Body_DamageFlg = true;

	if (WallFlg == false)return true;
	//���G�̏�����
	CountMNum = CountMStart;

	return true;
}

void C_CarBase::SetBPos(D3DXVECTOR3 RayPos, bool RayJudgFlg)
{
	brj.RayPos = RayPos;
	brj.JudgRayFlg = RayJudgFlg;
}

CHARAData C_CarBase::GetData(void)
{
	CHARAData c;
	c.NowMat = Car.Base.Mat;
	c.Rad = Car.Base.AttRad;
	c.CurFlg = Car.Con.CurFlg;
	c.NowGround = Car.Con.GroNum;
	c.DrawFlg = Car.Base.Flg;
	c.Mesh = Car.Mesh.DrawMesh.lpMesh;
	c.Speed = Car.Con.NowSpeed;
	return c;
}

QuaForMove C_CarBase::GetQuaForMove(void)
{
	Q.AnimeFrame = CarFM.AnimeFrame;
	Q.BodyHeight = CarFM.BodyHeight;
	Q.CurFlg = CarFM.CurFlg;
	Q.CurVec = CarFM.CurVec;
	Q.EndMat = CarFM.EndMat;
	Q.NowMat = Car.Base.Mat;
	Q.QuaInitFlg = CarFM.QuaInitFlg;
	Q.QuaMatInitFlg = CarFM.QuaMatInitFlg;
	Q.SpeedMul = CarFM.SpeedMul;
	Q.SpeedMulJudg = CarFM.SpeedMulJudg;
	Q.StartMat = CarFM.StartMat;
	Q.WayVec = CarFM.WayVec;
	return Q;
}

bool C_CarBase::UpdateCountM(void)
{
	CountMNum -= 1;
	if (CountMNum <= 0) {
		CountMNum = 0;
		return false;
	}
	return true;
}

void C_CarBase::Set_Move_Stop_Time(const int * Time, const int * Speed)
{
	if (MMove_Stop_Time > 0)return;

	MMove_Stop_Time += *Time;

	if (MMove_Stop_Time < 0)MMove_Stop_Time *= -1;

	Car.Con.NowSpeed = *Speed;
}

bool C_CarBase::BallJudgCar(const D3DXVECTOR3 * Pos, const float * Radius)
{
	D3DXVECTOR3 carPos = judg.SetPosM(&Car.Base.Mat);

	if (judg.BallJudg(Pos, &carPos, Radius))return true;

	return false;
}

bool C_CarBase::BallJudgCar(bool * JudgFlg, float * SmallDis,const D3DXMATRIX * EndMat, const float * Radius)
{
	float Dis = *Radius + GetBodRadCar()*GetScalPosCar().z;

	if (judg.BallJudg(SmallDis, &judg.SetPosM(EndMat), &judg.SetPosM(&GetForMoveEndMat()), &Dis, JudgFlg)) 
	{
		return true;
	}

	return false;
}

void C_CarBase::RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad)
{
	int carType = GetConstCar();

	if (BallJudgCar(&judg.SetPosM(&RD->Mat), Rad) != true)return;

	c_StructManager structManager;

	D3DXVECTOR3 Pos = judg.SetPosM(&RD->Mat);

	if (RayJudgCar(&Pos, &RD->Ray, BJD) == true)BJD->HitType = structManager.GetCarType(&carType, cc);

}

bool C_CarBase::capsuleJudg(float * sd, int * hitNum, const S_Capsule * c, const bool * ForMoveJudgFlg)
{
	GetCapsule(ForMoveJudgFlg);
	bool b = judg.colCapsuleCapsule(&capsule, c, sd, hitNum);
	return b;
}

void C_CarBase::capsuleInit(const bool *EndMatFlg)
{
	c_StructManager structManager;
	if (*EndMatFlg == false)
	{
		D3DXMATRIX Mat;
		D3DXMatrixTranslation(&Mat, 0.0f, -CarFM.BodyHeight, 0.0f);
		Mat = Mat * Car.Base.Mat;
		capsule = structManager.getCapsule(&Mat, &Car.Base.ScaPos, &Car.Mesh.ColMod.Data.BigVec, &Car.Mesh.ColMod.Data.SmallVec);
	}
	else {
		capsule = structManager.getCapsule(&ForMoveEndMat, &Car.Base.ScaPos, &Car.Mesh.ColMod.Data.BigVec, &Car.Mesh.ColMod.Data.SmallVec);
	}
}

int C_CarBase::GetConstCar(void)
{
	switch (M_Driver)
	{
	case Hit_Type_Player:
		return co_PlayerCar;
		break;
	case Hit_Type_Enemy:
		return co_EnemyCar;
		break;
	}

	return 0;
}

S_Capsule C_CarBase::GetCapsule(const bool * EndMatFlg)
{
	capsuleInit(EndMatFlg);
	return capsule;
}

D3DXMATRIX C_CarBase::getSparkInitMat(const float * MoveVecX, const bool *wallHitFlg)
{
	float rad = *MoveVecX;
	if (rad > 0.0f)rad = 1.0f;
	if (rad < 0.0f)rad = -1.0f;
	if (*wallHitFlg == true)rad *= -1.0f;
	rad = rad * capsule.r;
	
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, rad, 0.0f, 0.0f);
	tmp = tmp * Car.Base.Mat;
	return tmp;
}

void C_CarBase::SetSideTransMat(const float * MoveX)
{
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, *MoveX, 0.0f, 0.0f);
	Car.Base.Trans = trans * Car.Base.Trans;
	Car.Base.Mat = Car.Base.Trans*Car.Con.JudgMat;
}

bool C_CarBase::RayJudgCar(const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Ray, BULLETJUDGDATA * BJD)
{
	float Dis;

	if (judg.RayJudg_Mesh(Pos, Ray, &GetDrawMatCar(), Car.Mesh.DrawMesh.lpMesh, &Dis))
	{
		//���C�������������ɒe�̈ړ���Vec�̒������Z�������ׂ�
		if (Dis < BJD->SamllDis) {
			//�Z����
			BJD->SamllDis = Dis;
			return true;
		}
	}

	return false;
}

void C_CarBase::SetMeshCar(int MeshNo)
{
	C_CarMeshManager carMeshManager;

	Car.Mesh = carMeshManager.GetMesh(MeshNo);

	Car.Base.BodRad = judg.GetRad(&Car.Mesh.ColMod);
}

void C_CarBase::Update_Gun_Data(void)
{
	//�e�̓�����Data�̍X�V
	M_S_Gun_Update_Data.Gun_Stop_Flg = Get_Stop_Flg();
}

void C_CarBase::Update_Move_Stop_Time(void)
{
	if (MMove_Stop_Time <= 0)return;

	MMove_Stop_Time--;

	if (MMove_Stop_Time < 0)MMove_Stop_Time = 0;
}

bool C_CarBase::Get_Stop_Flg(void)
{
	//�����̊m�F
	if (Dead() == true)return true;

	//��������~���Ă��鎞�Ԃ��N�����Ă���Ǝ~�߂�
	if (Get_Move_Stop_Time() > 0)return true;

	return false;
}
