#include "EnemyAi.h"
#include"Data/No1/Speed/SpeedUp.h"

C_EnemyAi::C_EnemyAi()
{
	NowCount = MaxCount = 1;
	InitSpeedMove(new SpeedUp1());
	SpeedMul = 1.0f;

	//スピードの初期化
	Car.Con.NowSpeed = 80;
	Car.Con.MaxSpeed = 150;

	DeadFlg = false;
}

C_EnemyAi::~C_EnemyAi()
{
	if (speed != nullptr) {
		delete speed;
	}
	if (m_Ai != nullptr) {
		delete m_Ai;
	}
}

bool C_EnemyAi::UpdateAi(const CHARAData * cd, const int * Data_Num, const bool * End_Flg)
{
	if (*Data_Num <= 0) {
		return false;
	}
	if (GetHp() <= 0)Car.Base.Flg = false;

	if ((Car.Base.Flg == true) && (*End_Flg != true)) {
		if (m_Ai != nullptr) {
			C_E_AiPhaseBase *L_Ai;
			L_Ai = m_Ai->Action(&GetCharaBase(), carParts, gun, &M_S_Gun_Update_Data, &Car.Con.GroNum, &cd[0].NowGround);
			if (L_Ai != nullptr) {
				delete m_Ai;
				m_Ai = L_Ai;
			}
		}

		M_S_Gun_Update_Data.TargetPos = judg.SetPosM(&cd[0].NowMat);

		unsigned int GNo = cd[0].NowGround - 5;
		bool Flg = StartAi(&GNo);

	}

	//スピード
	C_Speed_Update *NextSpeed;

	bool CarFlg = GetFlgCar(), L_StopFlg = Get_Stop_Flg();

	// スピードの更新に必要な情報の作成
	s_AISpeedUpdateData SpeedData;
	SpeedData.AliveFlg = CarFlg;
	SpeedData.NowGroNo = Car.Con.GroNum;
	SpeedData.NowPhase = M_S_Gun_Update_Data.NowPhase;
	SpeedData.TargetSpeed = cd[0].Speed;
	SpeedData.TargetGroNo = cd[0].NowGround;
	SpeedData.UpdateStopFlg = L_StopFlg;

	// スピードの更新
	NextSpeed = speed->Update(&Car.Con.NowSpeed, &SpeedData);
	if (NextSpeed != nullptr) {
		delete speed;
		speed = NextSpeed;
	}
	Car.Con.Speed = D3DXVECTOR3(0.0f, 0.0f, (float)Car.Con.NowSpeed / 100.0f);

	return true;
}

bool C_EnemyAi::Update(std::vector<C_Ground_Object*> ground)
{
	UpdateCarFM(ground);

	return true;
}

void C_EnemyAi::SetParts(std::vector<C_Ground_Object*> ground)
{
	judg.MatMatVec(&brj.MoveVec, PlaMovMat, Car.Base.Mat);//MoveVec作成
	UpdateCar();
	//標準パーツのアップデート
	Update_Car_Parts();

	//銃の情報の更新
	Update_Gun_Data();

	//銃の動きの更新
	Update_Gun();

	if (Car.Base.Flg == true) {
		//無敵のアップデート
		UpdateCountM();
	}

	Update_Move_Stop_Time();

	UpdateCarEffect();
}



void C_EnemyAi::SetPlaEnd(bool Flg)
{
	/*if (Flg == true) {
		gun.AIFlg = false;
		gun.RayJudgFlg = false;
	}
	else {
		gun.AIFlg = true;
	}*/
}

bool C_EnemyAi::StartAi(const unsigned int * GNo)
{
	if (Car.Base.Flg != true) return false;
	//if (gun.AIFlg != false) return false;
	if (Car.Con.GroNum < *GNo) return false;
	
	//gun.AIFlg = true;
	return true;
}

void C_EnemyAi::InitSpeedMove(C_Speed_Update * Initspeed)
{
	if (speed != nullptr) {
		delete speed;
	}
	speed = Initspeed;
}

