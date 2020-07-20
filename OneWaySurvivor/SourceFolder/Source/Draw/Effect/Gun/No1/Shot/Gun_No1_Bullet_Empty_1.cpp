#include "Gun_No1_Bullet_Empty_1.h"
#include"../../../../../GameSource/Judgment.h"

C_Gun_No1_Bullet_Enpty::C_Gun_No1_Bullet_Enpty(const D3DXMATRIX * GunMat)
{
	Set_Mat(GunMat);

	Init_Bullet();
}

C_Gun_No1_Bullet_Enpty::~C_Gun_No1_Bullet_Enpty()
{
	if (M_Count == nullptr)return;

	delete M_Count;
}

void C_Gun_No1_Bullet_Enpty::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Get_MoveVecFlg();

	Mesh_Draw_No1();
}

void C_Gun_No1_Bullet_Enpty::Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (Get_MoveVecFlg() != true)return;

	Base_Set_MoveVec(MoveVec);

}

bool C_Gun_No1_Bullet_Enpty::Update(void)
{
	M_MoveVec.y += yDown;

	D3DXMATRIX TmpMat;

	Judg judg;

	judg.setTransMat(&TmpMat, &M_MoveVec);

	TmpMat = TmpMat * Get_Mat();

	Set_Mat(&TmpMat);

	return M_Count->Update_Count();
}

void C_Gun_No1_Bullet_Enpty::Init_Bullet(void)
{
	//ÉçÅ[Éh
	Mesh_Load("Bullet1-3.x");

	int Big = 40, Small = -20;
	Big = Big - Small;
	M_MoveVec = D3DXVECTOR3(0.07f, 0.065f + (float)(rand() % Big + Small) / 1000.0f, 0.0f);

	yDown = -0.01f;

	float Size = 0.22f;
	Set_ScalPos_Init(&Get_SizeVec(&Size));

	int c = 30;
	M_Count = new C_Count(&c);
}
