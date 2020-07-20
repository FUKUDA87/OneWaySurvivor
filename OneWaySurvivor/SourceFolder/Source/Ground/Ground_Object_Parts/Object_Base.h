#pragma once
#include"../../GameSource/Struct.h"
#include<string>

class C_Object_Base {
public:
	C_Object_Base();
	//表示
	virtual void Draw(void);

	//表示行列の更新
	virtual void Update_DrawMat(const D3DXMATRIX *Mat);

	//情報渡し
	S_Base3D_2 Get_Data(void) {
		return M_Base;
	}

	//表示Mesh渡し
	LPD3DXMESH Get_Mesh(void) {
		return M_Mesh.Mesh.lpMesh;
	}

	//表示Flgのセット
	void Set_DrawFlg(const bool *Flg) {
		M_Base.Base.DrawFlg = *Flg;
	}

	//行列の種類渡し
	unsigned int Get_Mat_No(void) {
		return M_Set_Mat_No;
	}

protected:
	//表示Mesh
	XFILE_B M_Mesh;

	//表示行列
	S_Base3D_2 M_Base;

	//行列の代入の種類
	unsigned int M_Set_Mat_No;

	//メッシュのロード
	void Mesh_Load(std::string FileName);

	//初期化
	virtual void Init(void);

private:


};