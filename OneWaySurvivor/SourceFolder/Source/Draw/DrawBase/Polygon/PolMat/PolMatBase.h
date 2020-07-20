#pragma once
#include"../PolygonBase.h"

class C_PolMatBase:public C_PolygonBase {
public:
	C_PolMatBase();
	~C_PolMatBase();
	//ポリゴンに移動量の加算
	void SetMat_MoveVec(const D3DXVECTOR3* MoveVec);

	//行列のたらい回し
	void SetMat_Mat(const D3DXMATRIX *Mat);
protected:
	//ポリゴン管理の変数
	PolygonMatrix M_Polygon;

	/*関数*/

	//nullチェックとポリゴン数のチェック(<=)
	bool PolMat_Judg(void);

	//nullチェックとポリゴン数のチェック(<=)
	bool PolMat_Judg(const int PolNum);

	//表示ポリゴン数の行列の変更
	void Init_PolMat(const int PolNum);
	//ポリゴン数の行列の削除
	void Delete_PolMat(void);
	//ポリゴン数の行列に通常の行列を入れる
	void Init_PolMat_Mat(const D3DXMATRIX *Mat);

	int Get_PolMatNum(void) {
		return M_Polygon.Num;
	}
private:

};