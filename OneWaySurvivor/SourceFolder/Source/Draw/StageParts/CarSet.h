#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Judgment.h"
#include"../DrawBase2/Draw3D_Base2.h"

class C_CarSet {
public:
	C_CarSet();
	~C_CarSet();

	void ChangeMode(const bool Flg);

	void DrawTxt(void);

	void Draw3D(const D3DXVECTOR3 *CameraPos);

	bool GetModeFlg(void) {
		return ModeFlg;
	}

	//呼び出したら車メッシュ変更
	void ChangeCar(void);

	D3DXVECTOR3 GetPartsPos(void) {
		return PartsPos;
	}

	void SetPartsPos(const D3DXVECTOR3* Pos) {
		PartsPos = *Pos;
	}

	float GetUp(void) {
		return 0.01f;
	}

	void ChangePartsMeshFlg(const bool Flg);

	void ChangePartsMesh(const bool Flg);

	void GroundSize(const float *H_Y);

	bool Get_Mesh_JudgFlg(void) {
		return M_Draw->Get_Draw_JudgFlg();
	}

	LPD3DXMESH Get_Mesh(void) {
		return M_Draw->Get_Mesh();
	}

protected:
	
private:
	bool ModeFlg;

	int PartsMeshFlg;

	XFILE Car;
	D3DXVECTOR3 PartsPos;

	C_Draw3D_Base2 *M_Draw;

	Judg judg;

	int CarMeshNo,ChangeMeshNo;

	float GroundY;//車からタイヤの下までの距離

	void Delete_Draw(void);

	void Change_Draw(C_Draw3D_Base2* Draw);

	//変更メッシュ
	void Change_Pol(void);
	void Change_Tire(void);
	void Change_Door(void);
	void Change_Vector(void);
};