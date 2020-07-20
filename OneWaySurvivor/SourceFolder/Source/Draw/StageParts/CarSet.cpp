#include "CarSet.h"
#include<stdio.h>
#include"../../MaterialManager/XfileManager.h"
#include"../../Car/Data/Draw3DManager/CarNoManager.h"
#include"../Tire/Car_Tire_No1.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"
#include"../DrawBase2/Draw_Pol_A.h"


extern XFileManager xfileManager;
extern LPD3DXFONT lpFontS;

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス


void DrawMesh(XFILE *XFile);

C_CarSet::C_CarSet()
{
	ModeFlg = false;
	CarMeshNo = 0;
	ChangeCar();
	PartsPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Vector = xfileManager.GetXfile("Vector1.x");
	Change_Draw(new C_Draw_Mesh_Base("tireP5.x"));
	PartsMeshFlg = 0;
	GroundY = 0.0f;
	ChangeMeshNo = 1;
}

C_CarSet::~C_CarSet()
{
	Delete_Draw();
}

void C_CarSet::ChangeMode(const bool Flg)
{
	if (Flg != true)return;

	judg.ReverseFlg(&ModeFlg);
}

void C_CarSet::DrawTxt(void)
{
	if (ModeFlg != true)return;

	RECT rcCon = { 0,0,0,0 };
	char TextB[200];
	sprintf_s(TextB, sizeof(TextB), "Xキー(赤X：緑Y：青Z：尖り＋)\nX:%f(-A:+F)\nY:%f(+W:-S)\nZ:%f(+E:-D)\nG:%f\n"
		,PartsPos.x, PartsPos.y, PartsPos.z,GroundY);
	lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void C_CarSet::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	if (ModeFlg != true)return;

	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0.0f, 0.0f, 0.0f);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
	DrawMesh(&Car);

	D3DXMATRIX PartsMat;
	judg.setTransMat(&PartsMat, &PartsPos);

	M_Draw->Set_Mat(&PartsMat);

	M_Draw->Draw3D(CameraPos);
}

void C_CarSet::ChangeCar(void)
{
	C_CarNoManager l_CarManager;
	CarMeshNo = l_CarManager.GetNextNo(&CarMeshNo);

	Car = l_CarManager.GetMesh(CarMeshNo).DrawMesh;

}

void C_CarSet::ChangePartsMeshFlg(const bool Flg)
{
	if (Flg != true)return;

	switch (PartsMeshFlg)
	{
	case 0:
		ChangeMeshNo = 1;
		PartsMeshFlg = 1;
		ChangePartsMesh(true);
		break;
	case 1:
		ChangeMeshNo = 1;
		PartsMeshFlg = 2;
		ChangePartsMesh(true);
		break;
	case 2:
		ChangeMeshNo = 1;
		PartsMeshFlg = 3;
		ChangePartsMesh(true);
		break;
	case 3:
		ChangeMeshNo = 1;
		PartsMeshFlg = 0;
		ChangePartsMesh(true);
		break;
	default:
		Change_Draw(new C_Draw_Mesh_Base("tireP5.x"));
		PartsMeshFlg = 0;
		break;
	}
}

void C_CarSet::ChangePartsMesh(const bool Flg)
{
	if (Flg != true)return;

	switch (PartsMeshFlg)
	{
	case 0:
		Change_Tire();
		break;
	case 1:
		Change_Vector();
		break;
	case 2:
		Change_Pol();
		break;
	case 3:
		Change_Door();
		break;
	default:
		Change_Draw(new C_Draw_Mesh_Base("tireP5.x"));
		PartsMeshFlg = 0;
		break;
	}
}

void C_CarSet::GroundSize(const float * H_Y)
{
	GroundY = 0.0f - PartsPos.y+(PartsPos.y-*H_Y);
}

void C_CarSet::Delete_Draw(void)
{
	if (M_Draw == nullptr)return;

	delete M_Draw;
}

void C_CarSet::Change_Draw(C_Draw3D_Base2 * Draw)
{
	Delete_Draw();

	M_Draw = Draw;
}

void C_CarSet::Change_Pol(void)
{
	switch (ChangeMeshNo)
	{
	case 1:
		Change_Draw(new C_Draw_Pol_BASE_A(&D3DXVECTOR3(-0.3f, 0.0f, 0.8f), &D3DXVECTOR3(0.3f, 0.0f, 0.8f)
			, &D3DXVECTOR3(0.3f, 0.0f, -0.8f), &D3DXVECTOR3(-0.3f, 0.0f, -0.8f)));
		ChangeMeshNo = 2;
		break;
	case 2:
		Change_Draw(new C_Draw_Pol_BASE_A(&D3DXVECTOR3(0.0f, 1.0f, 1.0f), &D3DXVECTOR3(0.0f, 1.0f, -1.0f)
			, &D3DXVECTOR3(0.0f, -1.0f, -1.0f), &D3DXVECTOR3(0.0f, -1.0f, 1.0f)));
		ChangeMeshNo = 3;
		break;
	case 3:
		Change_Draw(new C_Draw_Pol_BASE_A(&D3DXVECTOR3(0.5f, 1.0f, 0.0f), &D3DXVECTOR3(-0.5f, 1.0f, 0.0f)
			, &D3DXVECTOR3(-0.5f, -1.0f, 0.0f), &D3DXVECTOR3(0.5f, -1.0f, 0.0f)));
		ChangeMeshNo = 1;
		break;
	default:
		Change_Draw(new C_Draw_Pol_BASE_A(&D3DXVECTOR3(-0.3f, 0.0f, 0.8f), &D3DXVECTOR3(0.3f, 0.0f, 0.8f)
			, &D3DXVECTOR3(0.3f, 0.0f, -0.8f), &D3DXVECTOR3(-0.3f, 0.0f, -0.8f)));
		break;
	}
	
}

void C_CarSet::Change_Tire(void)
{
	switch (ChangeMeshNo)
	{
	case 1:
		Change_Draw(new C_Draw_Mesh_Base("tireP5.x"));
		ChangeMeshNo = 2;
		break;
	case 2:
		Change_Draw(new C_Draw_Mesh_Base("CarTire1-3-1.x"));
		ChangeMeshNo = 1;
		break;
	default:
		Change_Draw(new C_Draw_Pol_BASE_A(&D3DXVECTOR3(-0.3f, 0.0f, 0.8f), &D3DXVECTOR3(0.3f, 0.0f, 0.8f)
			, &D3DXVECTOR3(0.3f, 0.0f, -0.8f), &D3DXVECTOR3(-0.3f, 0.0f, -0.8f)));
		break;
	}
}

void C_CarSet::Change_Door(void)
{
	switch (ChangeMeshNo)
	{
	case 1:
		Change_Draw(new C_Draw_Mesh_Base("CarDoorA1-3-1.x"));
		ChangeMeshNo = 2;
		break;
	case 2:
		Change_Draw(new C_Draw_Mesh_Base("CarDoorB1-3-1.x"));
		ChangeMeshNo = 1;
		break;
	default:
		Change_Draw(new C_Draw_Pol_BASE_A(&D3DXVECTOR3(-0.3f, 0.0f, 0.8f), &D3DXVECTOR3(0.3f, 0.0f, 0.8f)
			, &D3DXVECTOR3(0.3f, 0.0f, -0.8f), &D3DXVECTOR3(-0.3f, 0.0f, -0.8f)));
		break;
	}
}

void C_CarSet::Change_Vector(void)
{
	switch (ChangeMeshNo)
	{
	case 1:
		Change_Draw(new C_Draw_Mesh_Base("Vector1.x"));
		ChangeMeshNo = 2;
		break;
	case 2:
		Change_Draw(new C_Draw_Mesh_Base("Car_O_201_Judg_1.x"));
		ChangeMeshNo = 1;
		break;
	default:
		Change_Draw(new C_Draw_Mesh_Base("Vector1.x"));
		break;
	}
}
