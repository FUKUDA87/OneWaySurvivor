#include "Bullet_Base.h"
#include"../../../../GameSource/Judgment.h"

C_Bullet_Base::C_Bullet_Base(const D3DXMATRIX *Mat)
{
	//çsóÒÇÃèâä˙âª
	Set_Mat(Mat);

	Init();
}

C_Bullet_Base::C_Bullet_Base(const D3DXMATRIX * Mat, const S_RayHitJudgData * RayData)
{
	//çsóÒÇÃèâä˙âª
	Set_Mat(Mat);

	//íeÇåXÇØÇÈèàóù
	RayPos_Bullet(RayData);

	Init();
}

C_Bullet_Base::~C_Bullet_Base()
{
	M_Draw_Delete_All();
}

void C_Bullet_Base::Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw.size() < 1)return;

	for (auto && b:M_Draw) {
		b->Draw3D(CameraPos);
	}
}

void C_Bullet_Base::MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (M_Draw.size() < 1)return;

	Judg judg;

	judg.VecMatIn(&M_Base.Mat, MoveVec);

	for (auto && b : M_Draw) {
		b->Set_MoveVec(MoveVec);
	}
}

void C_Bullet_Base::Set_S_BULLET(const int * BulletTypeNo)
{

}

void C_Bullet_Base::Set_Mat(const D3DXMATRIX * Mat)
{
	M_Base.Mat = *Mat;
}

bool C_Bullet_Base::Move(void)
{
	if (M_Count->Update_Count() != true)return false;

	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0.0f, 0.0f, M_S_Bullet.Speed);

	M_Base.Mat = TmpMat * M_Base.Mat;

	if (M_Draw.size() < 1)return true;

	for (auto && b : M_Draw) {
		b->Set_Mat(&M_Base.Mat);
	}

	return true;
}

void C_Bullet_Base::Delete_Count(void)
{
	if (M_Count == nullptr)return;

	delete M_Count;
}

S_PolMat_INIT C_Bullet_Base::Get_Init_S_PolMat_INIT(const D3DXMATRIX * Mat, const int TexNo, const int PolNum, const float PolSize)
{
	S_PolMat_INIT Init;
	Init.Mat = *Mat;
	Init.PolSize = PolSize;
	Init.TexNo = TexNo;
	Init.PolNum = PolNum;
	return Init;
}

S_TEX_POS C_Bullet_Base::Get_Tex_Pos(const int W, const int H)
{
	S_TEX_POS Pos;
	Pos.Width = W;
	Pos.Height = H;
	return Pos;
}

void C_Bullet_Base::Init_S_Bullet(void)
{
	M_S_Bullet.Damage = 1;
	M_S_Bullet.Speed = 1.0f;
}

void C_Bullet_Base::M_Draw_Delete_All(void)
{
	if (M_Draw.size() < 1)return;

	for (unsigned int b = 0; b < M_Draw.size(); b++) {
		delete M_Draw[b];
		M_Draw.erase(M_Draw.begin() + b);
		b--;
	}

}

void C_Bullet_Base::RayPos_Bullet(const S_RayHitJudgData * RayData)
{
	if (RayData->Flg != true)return;

	Judg judg;

	//íeÇ™è∆èÄÇÃï˚Ç…å¸Ç©Ç§èàóù
	double Ang, ang = 0.0f;
	D3DXMATRIX RotMat;
	judg.CroDot(M_Base.Mat, &RotMat, RayData->HitPos, D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Ang, ang, false);
	M_Base.Mat = RotMat* M_Base.Mat;
}

void C_Bullet_Base::Init(void)
{
	M_GroWal_Judg_Flg = true;

	int t = 600;
	M_Count = new C_Count(&t);
}
