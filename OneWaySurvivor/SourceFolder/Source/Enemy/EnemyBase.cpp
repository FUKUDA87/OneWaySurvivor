#include "EnemyBase.h"

C_EnemyBase::C_EnemyBase()
{
	InitEnemy();
}

C_EnemyBase::~C_EnemyBase()
{
	//矢印の削除
	delete Vect;

}

void C_EnemyBase::InitEnemy(void)
{
	int MaxHp = 50;// rand() % 10 + 45;
	SetHp(&MaxHp);
	Car.Con.DFlg = false;
	//前進用のクォータニオンの初期化
	CarFM.SpeedMulJudg = 1.0f;

	//矢印の初期化
	Vect = new Vector();

	M_Driver = Hit_Type_Enemy;

	//通常の敵
	M_BossFlg = false;
}

bool C_EnemyBase::UpdateCar(void)
{
	D3DXVECTOR3 pos, vec;
	judg.SetPosM(&pos, &Car.Base.Mat);
	vec = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	CHARABASE c=GetCharaBase();
	
	return true;
}

void C_EnemyBase::Draw3D(const D3DXVECTOR3 * CamPos)
{

	Draw3DCar();
	Draw_Car_Parts(CamPos);

	Draw_Gun(CamPos);
	if (Car.Base.Flg == true) {
		//ボス以外なら表示
		if (BodyData.CarBodyNo < 200) {
			CHARABASE c = GetCharaBase();
			Hpbar->Draw3D(&CharaBase, &Car.Base.Mat, CamPos, &Car.Base.ScaPos);
		}
	}
	Draw_Bullet(CamPos);
	DrawCarEffect(CamPos);
}

void C_EnemyBase::Draw2D(void)
{
	if (Car.Base.Flg == true) {
		Vect->Draw(Car.Base.Flg);
		Hpbar->Draw2D(&CharaBase);
	}
}

void C_EnemyBase::GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport,const D3DXVECTOR3 *CameraPos)
{
	D3DXMATRIX Pmat;

	judg.setTransMat(&Pmat,&M_S_Gun_Update_Data.TargetPos);

	judg.Pos2DPE(&Pos2D,&Car.Base.Mat, &Pmat,mProj,mView,Viewport);//矢印Pos作成
	Vect->Update(&Pos2D, &Car.Base.Mat,CameraPos);
}

bool C_EnemyBase::GetDeleFlg(void)
{
	if (Car.Base.Flg == true)return true;
	//if (BulletE.size() > 0)return true;
	return false;
}

void C_EnemyBase::SetParts(std::vector<C_Ground_Object*> ground)
{
	
}

bool C_EnemyBase::capsuleJudg(float * sd, int * hitNum, const S_Capsule * c, const bool * ForMoveJudgFlg)
{
	GetCapsule(ForMoveJudgFlg);
	bool b = judg.colCapsuleCapsule(&capsule, c, sd, hitNum);
	if ((b == true) && (M_BossFlg == true))*hitNum += 1;
	return b;
}

