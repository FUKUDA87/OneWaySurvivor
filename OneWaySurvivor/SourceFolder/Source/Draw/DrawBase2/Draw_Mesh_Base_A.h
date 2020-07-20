#pragma once
#include"Draw3D_Base2.h"

#include<string>


class C_Draw_Mesh_Base:public C_Draw3D_Base2 {
public:
	C_Draw_Mesh_Base();
	C_Draw_Mesh_Base(std::string FileName);
	C_Draw_Mesh_Base(std::string FileName,const D3DXVECTOR3 *ScalPos);

	//表示関数
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos, bool *Body_DamageFlg);

	//移動量のセット
	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//メッシュ渡し
	LPD3DXMESH Get_Mesh(void);

	//ポリゴンの頂点渡し
	D3DXVECTOR3 Get_Pol_Pos(const int *PosNo);

protected:

	/*メンバー変数*/
	XFILE M_Mesh;

	////////////////////////////////////////////
	/*メンバー関数*/
	///////////////////////////////////////////

	/*初期化*/
	void Init_Mesh(void);

	/*表示*/
	void Mesh_Draw_No1(void);

	//メッシュのロード
	void Mesh_Load(std::string FileName);
	
private:
};