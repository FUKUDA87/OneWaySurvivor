#include "Ground_Object.h"
#include"Ground_Object_Parts/Bill_Object_1.h"
#include"Ground_Object_Parts/Light_Object_1_R.h"

C_Ground_Object::C_Ground_Object(const int *i):C_Ground(i)
{

}

C_Ground_Object::C_Ground_Object(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4
	, const S_GROUND_INIT_DATA * Init_Data_Ground)
	: C_Ground(Mat3,Mat4, Init_Data_Ground)
{

}

C_Ground_Object::~C_Ground_Object()
{
	Delete_All_Object();
}

bool C_Ground_Object::Update()
{
	UpdateGround();

	Update_Object();

	return true;
}

void C_Ground_Object::Draw3D()
{
	Draw3DGround();
	Draw_Object();
}

S_Base3D_2 C_Ground_Object::Get_Object_Data(const unsigned int * No)
{
	return M_Object[*No]->Get_Data();
}

void C_Ground_Object::Set_DrawFlg_Object(const unsigned int * No,const bool *Flg)
{
	if ((*No < 0) || (*No >= M_Object.size()))return;

	M_Object[*No]->Set_DrawFlg(Flg);
}

void C_Ground_Object::Init_Bill(void)
{
	M_Object.push_back(new C_Bill_Object_1());
}

void C_Ground_Object::Init_Light(void)
{
	M_Object.push_back(new C_Light_Object_1());
	M_Object.push_back(new C_Light_Object_1_Reverse());
}

void C_Ground_Object::Update_Object(void)
{
	if (M_Object.size() <= 0)return;

	for (auto && o : M_Object) {
		unsigned int No = o->Get_Mat_No();
		o->Update_DrawMat(&Get_Object_SetMat(&No));
	}
}

void C_Ground_Object::Draw_Object(void)
{
	if (M_Object.size() <= 0)return;

	for (auto && o : M_Object) o->Draw();
	
}

void C_Ground_Object::Delete_All_Object(void)
{
	if (M_Object.size() <= 0)return;

	for (unsigned int o = 0; o < M_Object.size(); o++) {
		delete M_Object[o];
		M_Object.erase(M_Object.begin() + o);
		o--;
	}
}

D3DXMATRIX C_Ground_Object::Get_Object_SetMat(const unsigned int * No)
{
	return wall[*No]->GetMat();
}
