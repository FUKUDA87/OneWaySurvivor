#pragma once
#include"Draw3D_Base2.h"
#include"../../Draw/3D/Ball/Ball3D.h"
#include<vector>

class C_Draw_Ball_A :public C_Draw3D_Base2 {
public:
	C_Draw_Ball_A(const float Dis);
	~C_Draw_Ball_A();

	//表示関数
	void Draw3D(const D3DXVECTOR3 *CameraPos);

	//移動量のセット
	void Set_MoveVec(const D3DXVECTOR3 *MoveVec) {

	}

	//メッシュ渡し
	LPD3DXMESH Get_Mesh(void);

	//ポリゴンの頂点渡し
	D3DXVECTOR3 Get_Pol_Pos(const int *PosNo);

	//円の半径渡し
	float Get_Dis(void);

	//表示行列の渡し
	D3DXMATRIX Get_DrawMat(void) {
		return M_Mat;
	}
protected:
	float M_Dis;

	std::vector<c_Ball3D*>M_Ball;

	//全削除
	void Delete_All_Ball(void);

	int Count;
};