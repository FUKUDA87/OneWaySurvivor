#pragma once
#include"Draw_Pol_A.h"

class C_Draw_PolMat_Base_1 :public C_Draw_Pol_BASE_A {
public:
	C_Draw_PolMat_Base_1(std::string FileName, const S_TEX_POS *Pos);
	C_Draw_PolMat_Base_1(std::string FileName, const S_TEX_DRAW_DATA* Data);

	~C_Draw_PolMat_Base_1();

	//表示関数
	void Draw3D(const D3DXVECTOR3 *CameraPos);

	//移動量のセット
	void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//行列の渡し
	void Set_Mat(const D3DXMATRIX*Mat) {
		Set_PolMat_Mat(Mat);
	}

protected:

	/*メンバー変数*/


	//ポリゴン管理の変数
	PolygonMatrix M_Polygon;

	/*メンバー関数*/

	//nullチェックとポリゴン数のチェック(<1)
	bool PolMat_Judg(void);

	//nullチェックとポリゴン数のチェック(<PolNum)
	bool PolMat_Judg(const int PolNum);

	//表示ポリゴン数の行列の変更
	void Init_PolMat(const int PolNum);

	//ポリゴン数の行列の削除
	void Delete_PolMat(void);

	//ポリゴン数の行列に通常の行列を入れる
	void Init_PolMat_Mat(const D3DXMATRIX *Mat);

	//ポリゴン数の行列に行列を渡しながら入れる
	void Set_PolMat_Mat(const D3DXMATRIX *Mat);

	//
	virtual void PolMat_Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//ポリゴン数を渡す
	int Get_PolMatNum(void) {
		return M_Polygon.Num;
	}

	/*表示*/

	//弾に使用
	virtual void Draw_PolMat_No1(const D3DXVECTOR3 *CameraPos);

private:

};