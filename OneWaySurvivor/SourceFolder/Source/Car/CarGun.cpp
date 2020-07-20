#include "CarGun.h"
#include"../Draw/Gun/Draw/Move/GunMove_A_Manager_1.h"
#include"../Const/Const_PartsTypeNo.h"
#include"../Draw/Gun/Draw/Type/Gun_Gatling_1.h"
#include"../Draw/Gun/Draw/Gun_Draw_Manager.h"

C_CarGun::~C_CarGun()
{
	AllDelete_Gun();
}

void C_CarGun::Draw_Gun(const D3DXVECTOR3 * CameraPos)
{
	if (gun.size() < 1)return;

	for (unsigned int g = 0; g < gun.size(); g++) {
		gun[g]->Draw(CameraPos);
	}
}

void C_CarGun::Update_Gun(void)
{
	if (gun.size() < 1)return;

	D3DXVECTOR3 ScalPos;
	Judg judg_a;

	for (unsigned int g = 0; g < gun.size(); g++) {

		int JointNo = (int)g + 1;
		M_S_Gun_Update_Data.StandMat = Get_Joint_Mat(&JointNo);

		ScalPos = judg_a.GetVecVec(&Car.Base.ScaPos,
			&GetCarPartsSize(&GetDataNo(Co_Parts_Gun, JointNo)));
		gun[g]->Set_ScalPos(&ScalPos);

		gun[g]->Update(&M_S_Gun_Update_Data);
	}
}

C_GunMoveBase_A * C_CarGun::Get_GunMove(const int * MoveNo)
{
	C_GunMove_A_Manager_Base *Manager;
	Manager = new C_GunMove_A_Manager_1();

	return Manager->Get_GunMove_A(MoveNo);
}

void C_CarGun::Set_GunMove_Player(const unsigned int * GunNo)
{
	if (Judg_GunNo(GunNo) != true)return;

	if (gun[*GunNo]->Get_S_GUN_DATA().PlayerFlg != false)return;

	int i = 1;
	gun[*GunNo]->New_GunMove(Get_GunMove(&i));

}

void C_CarGun::New_Set_Car_Parts(const BODYDATA * CarData)
{
	New_Car_Parts_Data(&CarData->CarBodyNo);

	New_CarParts(CarData);

	New_Car_Judg_Parts();

	New_Car_Parts_Gun(CarData);

	if (M_Driver != Hit_Type_Player)DeleteCarPartsData();
}

void C_CarGun::New_Set_Car_Parts(const int * CarNo, std::vector<C_Parts_Set_Data*> M_Set_Data)
{
	New_Car_Parts_Data(CarNo);

	New_CarParts(M_Set_Data);

	New_Car_Judg_Parts();

	New_Car_Parts_Gun(M_Set_Data);

	if (M_Driver != Hit_Type_Player)DeleteCarPartsData();
}

void C_CarGun::New_Car_Parts_Gun(const BODYDATA * CarData)
{
	AllDelete_Gun();

	if (M_CarPartsData.size() < 1)return;

	C_Gun_Darw_Manager Manager;

	for (unsigned int d = 0; d < M_CarPartsData.size(); d++) {
		if (M_CarPartsData[d]->MeshTypeNo == Co_Parts_Gun)gun.push_back(Manager.Get_Gun_Stop(&CarData->GunNo));
	}
}

void C_CarGun::New_Car_Parts_Gun(std::vector<C_Parts_Set_Data*> M_Set_Data)
{
	AllDelete_Gun();

	if ((M_CarPartsData.size() < 1) || (M_Set_Data.size() < 1))return;

	C_Gun_Darw_Manager Manager;

	for (unsigned int d = 0; d < M_CarPartsData.size(); d++) {
		for (auto && s : M_Set_Data) {
			int DrawNo = s->Get_Data().DrawNo;
			if (M_CarPartsData[d]->MeshTypeNo == Co_Parts_Gun)gun.push_back(Manager.Get_Gun_Stop(&DrawNo));
		}
	}

}

void C_CarGun::RayJudgGun(BULLETJUDGDATA * BJD, const D3DXVECTOR3 * Pos, const int * CarType, const unsigned int * cc, const D3DXVECTOR3 * Ray)
{
	//èe
	if (gun.size() <= 0) return;

	c_StructManager structManager;

	int GunType = 0;
	switch (*CarType)
	{
	case co_PlayerCar:
		GunType = co_PlayerGun;
		break;
	case co_EnemyCar:
		GunType = co_EnemyGun;
		break;
	}

	for (unsigned int gc = 0; gc < gun.size(); gc++) {
		//if (enemy[e]->GetGunData(&g).Base.DrawFlg != true)continue;

		bool Flg = gun[gc]->Dead();
		if (judg.ReverseFlg2(&Flg) != true) continue;

		if (gun[gc]->Get_Draw_Parts_Num() <= 0) continue;

		for (unsigned int gpc = 0; gpc < gun[gc]->Get_Draw_Parts_Num(); gpc++) {

			if (gun[gc]->Get_Draw_Parts_Draw_JudgFlg(&gpc) != Co_Draw_Mesh) continue;

			//ÉåÉCîªíË
			if (judg.RayJudg_Mesh_SmallDis(Pos, Ray, &gun[gc]->Get_Draw_Parts_Draw_Mat(&gpc)
				, gun[gc]->Get_Draw_Parts_Mesh(&gpc), &BJD->SamllDis) != true) continue;

			BJD->HitType = structManager.GetCarType(&GunType, cc, &gc, &gpc);

		}
	}

}

void C_CarGun::Delete_Gun(unsigned int * GunNo)
{
	if (gun.size() < 1)return;
	unsigned int No = *GunNo;
	if ((No < 0) || (No >= gun.size()))return;

	delete gun[No];
	gun.erase(gun.begin() + No);
	No--;
	*GunNo = No;

	return;
}

bool C_CarGun::Judg_GunNo(const unsigned int * GunNo)
{
	if (gun.size() < 1)return false;

	if (*GunNo < 0)return false;
	if (*GunNo >= gun.size())return false;

	return true;
}

void C_CarGun::Set_Gun_Trigger(const unsigned int * GunNo, const bool * TriggerFlg)
{
	if (*GunNo < 0)return;

	if (*GunNo >= gun.size())return;

	gun[*GunNo]->Update_Trigger(TriggerFlg);
}

D3DXMATRIX C_CarGun::Get_Joint_Mat(void)
{
	D3DXMATRIX Mat=GetMatCar();

	if (carParts.size() < 1)return Mat;

	for (unsigned int p = 0; p < carParts.size(); p++){
		if (carParts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Gun) {
			Mat = carParts[p]->Get_Draw_Mat();
			if (carParts[p]->Get_Juint_Data_Num() > 0) {
				for (unsigned int d = 0; d < carParts[p]->Get_Juint_Data_Num(); d++) {
					D3DXMATRIX TmpMat;
					Judg judg_a;
					D3DXVECTOR3 Vec= carParts[p]->Get_Joint_Data(&d).TransPos;
					Vec = judg_a.GetVecVec(&carParts[p]->Get_Draw_ScalPos(), &Vec);
					judg_a.setTransMat(&TmpMat,&Vec);
					Mat = TmpMat * Mat;
					return Mat;
				}
			}
		}
	}

	return Mat;
}

D3DXMATRIX C_CarGun::Get_Joint_Mat(const int * JointNo)
{
	D3DXMATRIX Mat = GetMatCar();

	if (carParts.size() < 1)return Mat;

	for (unsigned int p = 0; p < carParts.size(); p++) {
		if ((carParts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Gun)&&(carParts[p]->Get_Parts_Data().MeshJointNo==*JointNo)) {
			Mat = carParts[p]->Get_Draw_Mat();
			if (carParts[p]->Get_Juint_Data_Num() > 0) {
				for (unsigned int d = 0; d < carParts[p]->Get_Juint_Data_Num(); d++) {
					D3DXMATRIX TmpMat;
					Judg judg_a;
					D3DXVECTOR3 Vec = carParts[p]->Get_Joint_Data(&d).TransPos;
					Vec = judg_a.GetVecVec(&carParts[p]->Get_Draw_ScalPos(), &Vec);
					judg_a.setTransMat(&TmpMat, &Vec);
					Mat = TmpMat * Mat;
					return Mat;
				}
			}
			return Mat;
		}
	}

	return Mat;
}

S_GUN_DATA C_CarGun::Get_Gun_Data(const unsigned int * DrawGunNo)
{
	return gun[*DrawGunNo]->Get_S_GUN_DATA();
}

int C_CarGun::Get_Gun_Draw_Parts_Draw_JudgFlg(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	if ((gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= gun.size()))return 0;
	return gun[*M_GunNo]->Get_Draw_Parts_Draw_JudgFlg(PartsNo);
}

D3DXVECTOR3 C_CarGun::Get_Gun_Draw_Parts_Pol_Pos(const unsigned int * M_GunNo, const unsigned int * PartsNo, const int * PolNo)
{
	if ((gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= gun.size()))return D3DXVECTOR3(0.0f,0.0f,0.0f);
	return gun[*M_GunNo]->Get_Draw_Parts_Pol_Pos(PartsNo,PolNo);
}

LPD3DXMESH C_CarGun::Get_Gun_Draw_Parts_Mesh(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	//if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return false;
	return gun[*M_GunNo]->Get_Draw_Parts_Mesh(PartsNo);
}

bool C_CarGun::Get_Gun_Draw_Parts_Iden_Flg(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	if ((gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= gun.size()))return false;
	return gun[*M_GunNo]->Get_Draw_Parts_Iden_Flg(PartsNo);
}

D3DXMATRIX C_CarGun::Get_Gun_Draw_Parts_Draw_Mat(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	//if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return false;
	return gun[*M_GunNo]->Get_Draw_Parts_Draw_Mat(PartsNo);
}

bool C_CarGun::Damage_Gun(const unsigned int * M_GunNo, const int * Damage)
{
	return gun[*M_GunNo]->HpDamage(Damage);
}

bool C_CarGun::Ray_Judg_Gun_Flg(const unsigned int * M_GunNo)
{
	if ((gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= gun.size()))return false;
	Judg L_judg;
	bool Flg = gun[*M_GunNo]->Dead();
	return L_judg.ReverseFlg2(&Flg);
}

void C_CarGun::Set_Ray_Dis(const unsigned int * M_GunNo, const float * Dis)
{
	gun[*M_GunNo]->GetDis(Dis);
}

void C_CarGun::Set_Gun_Bullet_No(const unsigned int * M_GunNo, const int * BulletNo)
{
	if (*M_GunNo >= gun.size())return;

	gun[*M_GunNo]->Set_Bullet_No(BulletNo);
}

void C_CarGun::RayJudg(BULLETJUDGDATA * BJD, const unsigned int * cc, const RAYDATA * RD, const float * Rad)
{
	int carType = GetConstCar();

	if (BallJudgCar(&judg.SetPosM(&RD->Mat), Rad) != true)return;

	c_StructManager structManager;

	D3DXVECTOR3 Pos = judg.SetPosM(&RD->Mat);

	// é‘ëÃîªíË
	if (RayJudgCar(&Pos, &RD->Ray, BJD) == true)BJD->HitType = structManager.GetCarType(&carType, cc);

	// ÉpÅ[ÉcîªíË
	RayJudgParts(BJD, &Pos, &carType, cc, &RD->Ray);

	// èeîªíË
	RayJudgGun(BJD, &Pos, &carType, cc, &RD->Ray);
}

void C_CarGun::AllDelete_Gun(void)
{
	if (gun.size() < 1)return;

	for (unsigned int g = 0; g < gun.size(); g++) {
		Delete_Gun(&g);
	}
}
