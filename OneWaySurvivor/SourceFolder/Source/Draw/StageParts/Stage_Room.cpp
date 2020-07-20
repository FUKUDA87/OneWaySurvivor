#include "Stage_Room.h"
#include"../../GameSource/Judgment.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Stage_Room_Stand::C_Stage_Room_Stand(const D3DXVECTOR3 * Set_Pos, std::string FileName)
{

	M_Stand_Pos = *Set_Pos;
	New_Garage_Stand(FileName);
	M_Garage_Stand->Set_ScalPos_Update(&D3DXVECTOR3(1.5f, 1.5f, 1.5f));

}

C_Stage_Room_Stand::~C_Stage_Room_Stand()
{
	Delete_Garage_Stand();
}

void C_Stage_Room_Stand::Draw_Garage_Stand(const D3DXVECTOR3 * CameraPos)
{
	if (M_Garage_Stand == nullptr)return;

	M_Garage_Stand->Draw3D(CameraPos);
}

bool C_Stage_Room_Stand::Update_Garage_Stand(void)
{

	if (M_Garage_Stand == nullptr)return true;

	Set_Mat_Garage_Stand();

	return M_Garage_Stand->Update();
}

void C_Stage_Room_Stand::Delete_Garage_Stand(void)
{
	if (M_Garage_Stand == nullptr)return;

	delete M_Garage_Stand;
}

void C_Stage_Room_Stand::Set_Mat_Garage_Stand(void)
{
	if (M_Garage_Stand == nullptr)return;

	Judg judg;

	M_Garage_Stand->Set_Mat(&judg.getTransMat(&M_Stand_Pos));
}

void C_Stage_Room_Stand::New_Garage_Stand(std::string FileName)
{
	Delete_Garage_Stand();

	M_Garage_Stand = new C_Draw_Mesh_Base(FileName);
}
