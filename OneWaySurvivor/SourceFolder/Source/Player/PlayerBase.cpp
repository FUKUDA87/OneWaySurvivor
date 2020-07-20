#include "PlayerBase.h"
#include"../Draw/Bullet/Bullet_DrawManager.h"
#include"../Draw/Hp/Player/Hpbar2DPlayer.h"

C_PlayerBase::C_PlayerBase()
{
	InitPlayer();
	Init_Ray_Data();
}

C_PlayerBase::~C_PlayerBase()
{
	//セーブtxt
	if (fopen_s(&fp, "../GameFolder/Data/playerDate.txt", "w") == 0) {
		fprintf_s(fp, "%d", Car.Sta.CharaBase.MaxHp);
		fclose(fp);
	}
}

void C_PlayerBase::InitPlayer(void)
{
	//必須初期化-------------------------------------------------------------------------------
	//HPの初期化
	//ロードtxt
	if (fopen_s(&fp, "../GameFolder/Data/playerDate.txt", "r") == 0) {
		fscanf_s(fp, "%d", &Car.Sta.CharaBase.MaxHp);
		fclose(fp);
	}
	SetHp(&Car.Sta.CharaBase.MaxHp);

	Car.Base.AttRad = 1.0f / 2.0f;
	//スピードの初期化
	Car.Con.NowSpeed = 80;
	Car.Con.MaxSpeed = 150;
	Car.Con.Speed = D3DXVECTOR3(0.0f, 0.0f, (float)Car.Con.NowSpeed/100.0f);//0.8f

	Car.Con.CurFlg = false;
	RadField = 1000.0f*0.55f;
	Car.Con.GroNum = 0;
	//ball = new Ball(player.Base.BodRad);//(player.Base.rad);
	Hpbar->Init(new c_Hpbar2DPlayer());
	Car.Con.PEFlg = false;

	/*D3DXMATRIX spS, spE;
	D3DXMatrixTranslation(&spS, 0.0f, 0.0f, 1.1f);
	D3DXMatrixTranslation(&spE, 0.0f, 0.0f, -1.1f);*/
	/*spear = new Spear(spS, spE);
	vector = new Vector();*/

	//カーブ
	CurAng = 0.0f;


	M_Driver = Hit_Type_Player;
}

bool C_PlayerBase::Update(void)
{
	//移動ベクトル計算
	judg.MatMatVec(&brj.MoveVec, PlaMovMat, Car.Base.Mat);
	UpdateCar();

	if (Car.Base.Flg == true) {
		//無敵のアップデート
		UpdateCountM();

		//標準パーツのアップデート
		Update_Car_Parts();

		Update_Gun();
	}

	UpdateCarEffect();

	if (Dead()==true) {
		if (Car.Base.Flg == true) {
			Car.Base.Flg = false;
		}
		return false;
	}
	return true;
}

void C_PlayerBase::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	Draw3DCar();
	if (Car.Base.Flg == true) {
		Draw_Car_Parts(CameraPos);

		Draw_Gun(CameraPos);
	}
	Draw_Bullet(CameraPos);
	DrawCarEffect(CameraPos);
}

void C_PlayerBase::Draw2D(void)
{
	Hpbar->Draw2D(&CharaBase);
}

void C_PlayerBase::SetRodAngY(float Inc, bool KeyFlg)
{
	float MaxInc, SmallInc;
	if (Inc < 0.0f) {
		MaxInc = Inc * -1.0f;
		SmallInc = Inc;
	}
	else {
		MaxInc = Inc;
		SmallInc = Inc * -1.0f;
	}
	if (KeyFlg == true) {
		CurAng += Inc;
		float Over = 10.0f;
		if (CurAng < -Over)CurAng = -Over;
		if (CurAng > Over)CurAng = Over;
	}
	else {
		if (CurAng < 0.0f) {
			if (CurAng < SmallInc) {
				CurAng += MaxInc;
			}
			else {
				CurAng = 0.0f;
			}
		}
		else {
			if (CurAng > MaxInc) {
				CurAng -= MaxInc;
			}
			else {
				CurAng = 0.0f;
			}
		}
	}
}

void C_PlayerBase::SetCurRotMat(void)
{
	D3DXMatrixRotationY(&CurRotMatY, D3DXToRadian(CurAng));
	Car.Base.Mat = CurRotMatY * Car.Base.Mat;
}

bool C_PlayerBase::UpdateBulPla(const bool * KeyFlg, const bool * BirthFlg, const SoundCamera * sc)
{
	//弾を撃つと音とKey
	//UpdateBullet(&brj, KeyFlg, BirthFlg, sc);
	return true;
}

void C_PlayerBase::Set_CameraMat(const D3DXMATRIX * CameraMat)
{
	M_S_Gun_Update_Data.CameraMat = *CameraMat;
	unsigned int i = 0;
	Set_GunMove_Player(&i);
}

void C_PlayerBase::Shot(void)
{
	if (gun.size() < 1)return;

	C_Bullet_DrawManager Bullet_Manager;

	for (unsigned int g = 0; g < gun.size(); g++) {
		gun[g]->Init_Departure_Num();
		for (unsigned int i = 0; i < gun[g]->Get_CategoryNum(); i++) {
			if (gun[g]->Get_TriggerFlg(&i) == true) {
				int b = gun[g]->Get_BulletNo();
				D3DXMATRIX Mat = gun[g]->Get_GunMouth_Mat(&i);
				bullet.push_back(Bullet_Manager.Get_Bullet(&b, &Mat, &Get_Gun_Ray_Data()));
				gun[g]->Bullet_Shot_Update(&i);
				ShotEffect(&g, &i);
				S_SOUND_DATA Data;
				Data.Sound_Type = Co_Sound_Type_2D;
				Data.Sound_CategoryNo = Co_Sound_Category_Bullet;
				Data.Sound_No = 1;
				Data.Change_Type = Co_SoundNew;
				New_Sound_Data(&Data);
			}
		}
	}
}

void C_PlayerBase::RayJudg(BULLETJUDGDATA * BJD, const unsigned int * cc, const RAYDATA * RD, const float * Rad)
{
	int carType = GetConstCar();

	D3DXVECTOR3 Pos = judg.SetPosM(&RD->Mat);

	if (BallJudgCar(&Pos, Rad) != true)return;

	c_StructManager structManager;

	if (RayJudgCar(&Pos, &RD->Ray, BJD) == true)BJD->HitType = structManager.GetCarType(&carType, cc);

	//プレイヤーはパーツと銃判定をしない
}

void C_PlayerBase::Init_Ray_Data(void)
{
	M_Gun_Ray_Data.Flg = false;
}
