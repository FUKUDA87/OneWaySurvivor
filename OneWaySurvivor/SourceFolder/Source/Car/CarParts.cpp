#include "CarParts.h"
#include"../Draw/Tire/Car_Tire_No1.h"
#include"../Draw/Stand/Stand_No1.h"
#include"../Draw/Tire/Tire_DrawManager.h"
#include"../Draw/Door/Door_DrawManager.h"
#include"../Draw/Stand/Stand_DrawManager.h"

C_CarParts::C_CarParts()
{
	M_Parts_Save_Flg = true;
}

C_CarParts::~C_CarParts()
{
	Delete_ALL_Parts();
	DeleteCarPartsData();
	DeleteCarPartsSize();
}

void C_CarParts::Draw_Car_Parts(const D3DXVECTOR3 * CameraPos)
{
	if (carParts.size() < 1)return;

	for (auto && p : carParts) {
		p->Draw_Parts(CameraPos);
	}
}

bool C_CarParts::Update_Car_Parts(void)
{
	if (carParts.size() < 1)return false;

	D3DXVECTOR3 ScalPos;
	for (auto && p : carParts) {

		ScalPos = GetCarPartsSize(&GetDataNo(p->Get_Parts_Data().MeshTypeNo, p->Get_Parts_Data().MeshJointNo));

		p->UpdateParts(&GetMatCar(), &Car.Con.NowSpeed,&Car.Con.MaxSpeed,&Car.Base.ScaPos,&ScalPos);
	}
	return true;
}

void C_CarParts::Delete_Parts(unsigned int * PartsNo)
{
	if (carParts.size() < 1)return;

	unsigned int i = carParts.size();
	if (judg.Hit_No(PartsNo, &i) != true)return;

	delete carParts[*PartsNo];
	carParts.erase(carParts.begin() + (*PartsNo));
	*PartsNo -= 1;
}

D3DXMATRIX C_CarParts::Get_Camera_Mat(void)
{
	D3DXMATRIX Mat = GetMatCar();
	D3DXMATRIX tMat;
	D3DXMatrixTranslation(&tMat, 0.0f, 0.2f, 0.0f);
	Mat = tMat * Mat;

	if (M_CarPartsData.size() < 1)return Mat;

	for (unsigned int d = 0; d < M_CarPartsData.size(); d++) {
		if (M_CarPartsData[d]->MeshTypeNo == Co_Parts_Gun) {
			D3DXMATRIX TmpMat;
			Judg judg_a;
			judg_a.setTransMat(&TmpMat, &M_CarPartsData[d]->TransPos);
			Mat = TmpMat * Mat;
			break;
		}
	}

	return Mat;
}

bool C_CarParts::Damage_CarParts(const unsigned int * M_CarPartsNo, const int * Damage)
{
	bool DamageFlg;

	DamageFlg = carParts[*M_CarPartsNo]->HpDamage(Damage);

	int Flg = carParts[*M_CarPartsNo]->Get_Parst_DamageSet_Flg();
	if (Flg <= 0)return DamageFlg;

	if (HpDamage(&Flg, Damage) == true) DamageFlg = true;

	return DamageFlg;
}

void C_CarParts::RayJudg(BULLETJUDGDATA * BJD, const unsigned int * cc
	, const RAYDATA * RD, const float * Rad)
{
	int carType = GetConstCar();

	if (BallJudgCar(&judg.SetPosM(&RD->Mat), Rad) != true)return;

	c_StructManager structManager;

	D3DXVECTOR3 Pos = judg.SetPosM(&RD->Mat);

	if (RayJudgCar(&Pos, &RD->Ray, BJD) == true)BJD->HitType = structManager.GetCarType(&carType, cc);

	RayJudgParts(BJD, &Pos, &carType, cc, &RD->Ray);

}

void C_CarParts::BallJudgParst(BULLETJUDGDATA * BJD, const D3DXVECTOR3 * Pos, const int * CarType, const unsigned int * cc, const D3DXVECTOR3 * Ray,const float *Rad)
{

	if (judg.BallJudg(Pos, &judg.SetPosM(&Car.Base.Mat), Rad) != true)return;

	/*パーツ*/
	if (carParts.size() <= 0)return;

	c_StructManager structManager;

	int PartsType = 0;

	switch (*CarType)
	{
	case co_PlayerCar:
		PartsType=co_PlayerParts;
		break;
	case co_EnemyCar:
		PartsType= co_EnemyParts;
		break;
	}

	for (unsigned int pc = 0; pc < carParts.size(); pc++) {

		if (carParts[pc]->Get_Draw_Draw_JudgFlg() != Co_Draw_Ball) continue;

		float L_Radius = carParts[pc]->Get_Draw_Dis();

		if (judg.BallJudg(Pos, &judg.SetPosM(&carParts[pc]->Get_Draw_DrawMat()),
			&L_Radius) != true) continue;

		//最大より小さいか
		BJD->HitType = structManager.GetCarType(&co_EnemyParts, cc, &pc);

	}
	
}


void C_CarParts::New_CarParts(const BODYDATA * CarData)
{
	Delete_ALL_Parts();

	C_Tire_DrawManager Tire_Manager;
	C_Door_DrawManager Door_Manager;
	C_Stand_DrawManager Stand_Manager;


	//部位にパーツのセット
	/*
	※jointNoがマイナスの時は動きをリバース
	*/
	for (unsigned int d = 0; d < M_CarPartsData.size(); d++) {
		if (M_CarPartsData[d]->MeshTypeNo == Co_Parts_Tire)carParts.push_back(Tire_Manager.Get_Draw_Tire(&CarData->TireNo,M_CarPartsData[d]));
		if(M_CarPartsData[d]->MeshTypeNo == Co_Parts_Gun)carParts.push_back(Stand_Manager.Get_Draw_Stop(&CarData->StandNo, M_CarPartsData[d]));
		float Ang = 135.0f;
		if (M_CarPartsData[d]->MeshTypeNo == Co_Parts_Door)carParts.push_back(Door_Manager.Get_Draw_Door(&CarData->TireNo, M_CarPartsData[d],&Ang));
	}


}

void C_CarParts::New_CarParts(std::vector<C_Parts_Set_Data*> M_Set_Data)
{
	Delete_ALL_Parts();

	C_Tire_DrawManager Tire_Manager;
	C_Door_DrawManager Door_Manager;
	C_Stand_DrawManager Stand_Manager;


	//部位にパーツのセット
	/*
	※jointNoがマイナスの時は動きをリバース
	*/

	if ((M_CarPartsData.size() < 1) || (M_Set_Data.size() < 1))return;

	for (auto && d : M_CarPartsData) {
		for (auto && s : M_Set_Data) {

			int JointNo = d->MeshJointNo;
			if (JointNo < 0)JointNo *= -1;

			if ((d->MeshTypeNo == s->Get_Data().MeshTypeNo) && (JointNo == s->Get_Data().MeshJointNo)) {

				int DrawNo = s->Get_Data().DrawNo;
				float Ang = 135.0f;

				switch (d->MeshTypeNo)
				{
				//タイヤ
				case Co_Parts_Tire:
					carParts.push_back(Tire_Manager.Get_Draw_Tire(&DrawNo, d));
					break;
				//スタンド
				case Co_Parts_Gun:
					carParts.push_back(Stand_Manager.Get_Draw_Stop(&DrawNo,d));
					break;
				//ドア
				case Co_Parts_Door:
					carParts.push_back(Door_Manager.Get_Draw_Door(&DrawNo, d, &Ang));
					break;

				default:
					break;
				}

			}
		}
	}
}

S_CAR_PARTS_DATA* C_CarParts::Get_Data_CarParts(const int * TypeNo, const int JointNo)
{
	for (auto && d : M_CarPartsData) {
		int L_JointNo = d->MeshJointNo;
		if (L_JointNo < 0)L_JointNo *= -1;
		if ((d->MeshTypeNo == *TypeNo) && (L_JointNo == JointNo))return d;
	}

	return nullptr;
}

void C_CarParts::New_Car_Parts_Data(const int * CarNo)
{
	DeleteCarPartsData();

	C_CarDataManager Manager;

	int PartsNum = Manager.GetDrawNum(*CarNo, M_Parts_Save_Flg);

	for (int i = 0; i < PartsNum; i++) {
		SetCarPartsData(&Manager.GetDrawSet(*CarNo, &i, &M_Parts_Save_Flg));
	}
}

void C_CarParts::New_Car_Judg_Parts(void)
{
}

void C_CarParts::NewCarPartsSize(const int TypeNo, const int JointNo, const D3DXVECTOR3 * ScalPos)
{
	M_CarPartsSize.push_back(new C_Parts_Set_Size(&TypeNo, &JointNo, ScalPos));
}

void C_CarParts::NewCarPartsSize(const int TypeNo, const int JointNo, const float Size)
{
	M_CarPartsSize.push_back(new C_Parts_Set_Size(&TypeNo, &JointNo, &D3DXVECTOR3(Size, Size, Size)));
}

D3DXVECTOR3 C_CarParts::GetCarPartsSize(const S_PARTS_SET_DATA_No * No)
{
	if (M_CarPartsSize.size() < 1)return D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	for (auto && p : M_CarPartsSize) {
		if (No->MeshTypeNo == p->Get_Data().No.MeshTypeNo) {
			if (No->MeshJointNo == p->Get_Data().No.MeshJointNo) {
				return p->Get_Data().ScalPos;
			}
		}
	}

	return D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

S_PARTS_SET_DATA_No C_CarParts::GetDataNo(const int TypeNo, const int JointNo)
{
	S_PARTS_SET_DATA_No No;
	No.MeshTypeNo = TypeNo;
	No.MeshJointNo = JointNo;
	return No;
}

void C_CarParts::DeleteCarPartsData(void)
{
	if (M_CarPartsData.size() < 1)return;

	for (unsigned int d = 0; d < M_CarPartsData.size(); d++) {
		delete M_CarPartsData[d];
		M_CarPartsData.erase(M_CarPartsData.begin() + d);
		d--;
	}
}

void C_CarParts::RayJudgParts(BULLETJUDGDATA * BJD, const D3DXVECTOR3 * Pos
	, const int * CarType, const unsigned int * cc, const D3DXVECTOR3 * Ray)
{
	//パーツ
	if (carParts.size() <= 0) return;

	c_StructManager structManager;

	int PartsType = 0;
	switch (*CarType)
	{
	case co_PlayerCar:
		PartsType = co_PlayerParts;
		break;
	case co_EnemyCar:
		PartsType = co_EnemyParts;
		break;
	}

	for (unsigned int pc = 0; pc < carParts.size(); pc++) {
		//if (enemy[e]->GetPartsData(&p).MeshDrawFlg <= 0)continue;

		//メッシュ判定
		if (carParts[pc]->Get_Draw_Draw_JudgFlg() == Co_Draw_Mesh) {

			//表示行列
			D3DXMATRIX DrawMat = carParts[pc]->Get_Draw_DrawMat();

			//レイ判定
			if (judg.RayJudg_Mesh_SmallDis(Pos, Ray, &DrawMat
				, carParts[pc]->Get_Draw_Mesh(), &BJD->SamllDis) != true) continue;

			BJD->HitType = structManager.GetCarType(&PartsType, cc, &pc);

		}
		else {
			//板ポリゴン判定
			if (carParts[pc]->Get_Draw_Draw_JudgFlg() == Co_Draw_Pol) {

				int a = 0, b = 1, c = 2, d = 3;

				//レイ判定
				if (judg.RayJudg_Polygon_SmallDis(Pos, Ray, &carParts[pc]->Get_Draw_DrawMat(),
					&carParts[pc]->Get_Draw_Pol_Pos(&a), &carParts[pc]->Get_Draw_Pol_Pos(&b)
					, &carParts[pc]->Get_Draw_Pol_Pos(&c), &carParts[pc]->Get_Draw_Pol_Pos(&d)
					, &BJD->SamllDis) != true) continue;

				BJD->HitType = structManager.GetCarType(&PartsType, cc, &pc);

			}
		}
	}
}

void C_CarParts::SetCarPartsData(const S_CAR_PARTS_DATA * Data)
{
	M_CarPartsData.push_back(new S_CAR_PARTS_DATA);
	*M_CarPartsData[M_CarPartsData.size() - 1] = *Data;
}

S_CAR_PARTS_DATA C_CarParts::GetCarPartsData(const unsigned int * PartsNo)
{
	return *M_CarPartsData[*PartsNo];
}

void C_CarParts::DeleteCarPartsSize(void)
{
	if (M_CarPartsSize.size() < 1)return;

	for (unsigned int p = 0; p < M_CarPartsSize.size(); p++) {
		delete M_CarPartsSize[p];
		M_CarPartsSize.erase(M_CarPartsSize.begin() + p);
		p--;
	}
}

void C_CarParts::New_Set_Car_Parts(const BODYDATA * CarData)
{
	New_Car_Parts_Data(&CarData->CarBodyNo);

	New_CarParts(CarData);

	New_Car_Judg_Parts();

	if (M_Driver!=Hit_Type_Player)DeleteCarPartsData();
}

void C_CarParts::New_Set_Car_Parts(const int * CarNo, std::vector<C_Parts_Set_Data*> M_Set_Data)
{
	New_Car_Parts_Data(CarNo);

	New_CarParts(M_Set_Data);

	New_Car_Judg_Parts();

	if (M_Driver != Hit_Type_Player)DeleteCarPartsData();
}

void C_CarParts::Delete_ALL_Parts(void)
{
	if (carParts.size() < 1)return;

	for (unsigned int p = 0; p < carParts.size(); p++) {
		delete carParts[p];
		carParts.erase(carParts.begin() + p);
		p--;
	}
}

