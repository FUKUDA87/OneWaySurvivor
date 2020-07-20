#include "Car_Parts_Base.h"

C_Car_Parts_Base::C_Car_Parts_Base(const S_CAR_PARTS_DATA * set_Data)
{
	M_Parts_Data = *set_Data;
	Set_TransPos(&M_Parts_Data.TransPos);
	M_I_MoveFlg = 0;
}

C_Car_Parts_Base::~C_Car_Parts_Base()
{
	Move_Delete();
}

void C_Car_Parts_Base::Draw_Parts(const D3DXVECTOR3 * CameraPos)
{
	if (Dead() != false)return;

	Draw_Draw(CameraPos);
}

bool C_Car_Parts_Base::UpdateParts(const D3DXMATRIX * Mat)
{
	//動きのアップデート
	M_Base3D.Mat = *Mat;

	C_Move_Parts_Base *L_Move;
	int NowPhase = 0;
	bool MoveFlg = true;
	if (M_Move != nullptr) {
		L_Move = M_Move->Move(&M_Base3D, &M_Parts_Data, &Speed, &CharaBase, &NowPhase, &MoveFlg, &Get_Car_ScalPos(),&M_I_MoveFlg);
		if (L_Move != nullptr) {
			New_Move(L_Move);
		}
	}

	//表示のアップデート
	Set_All_Draw_Mat(&M_Base3D.Mat);

	return true;
}

bool C_Car_Parts_Base::UpdateParts(const D3DXMATRIX * Mat, const int *GetNowSpeed, const int *GetMaxSpeed
	, const D3DXVECTOR3* Car_ScalPos, const D3DXVECTOR3* Parts_ScalPos)
{
	SetSpeed(GetNowSpeed, GetMaxSpeed);

	Set_ScalPos_Body(Car_ScalPos,Parts_ScalPos);

	UpdateParts(Mat);

	return true;
}

S_CAR_PARTS_DATA C_Car_Parts_Base::Get_S_PARTS_DATA(const D3DXVECTOR3 TransPos, const D3DXVECTOR3 Ang)
{
	S_CAR_PARTS_DATA Data;
	Data.TransPos = TransPos;
	Data.Ang = Ang;
	Data.MeshTypeNo = 0;
	Data.MeshJointNo = 1;
	return Data;
}

void C_Car_Parts_Base::Move_Delete(void)
{
	if (M_Move == nullptr)return;

	delete M_Move;
}

void C_Car_Parts_Base::New_Move(C_Move_Parts_Base * New)
{
	Move_Delete();

	M_Move = New;
}

void C_Car_Parts_Base::Set_I_MoveFlg(const int Flg)
{
	int i = Flg;
	if (i < 0)i = 0;
	if (i > 2)i = 0;

	M_I_MoveFlg = i;
}

D3DXMATRIX C_Car_Parts_Base::Get_Draw_Mat(void)
{
	if (M_Draw == nullptr)return M_Base3D.Mat;

	return M_Draw->Get_Mat();
}

D3DXMATRIX C_Car_Parts_Base::Get_Draw_DrawMat(void)
{
	if (M_Draw == nullptr)return M_Base3D.Mat;

	return M_Draw->Get_DrawMat();
}
