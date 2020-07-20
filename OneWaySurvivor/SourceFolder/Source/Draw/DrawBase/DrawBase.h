#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_DrawBase {
public:
	C_DrawBase();
	//構造体の情報渡し
	S_DrawBase Get_S_DrawBase(void) {
		return M_S_DrawBase;
	}
	//構造体のセット
	void Set_S_DrawBase(const S_DrawBase* s_db) {
		M_S_DrawBase = *s_db;
	}

	//構造体の行列の代入
	void Set_S_DrawBase_Mat(const D3DXMATRIX *Mat) {
		M_S_DrawBase.Mat = *Mat;
	}
	//構造体の位置の代入
	void Set_S_DrawBase_Pos(const D3DXVECTOR3 *Pos) {
		M_S_DrawBase.Pos = *Pos;
	}
	//構造体の移動の代入
	void Set_S_DrawBase_TransPos(const D3DXVECTOR3 *TransPos) {
		M_S_DrawBase.TransPos = *TransPos;
	}
	//構造体のサイズの代入
	void Set_S_DrawBase_ScalPos(const D3DXVECTOR3 *ScalPos) {
		M_S_DrawBase.ScalPos = *ScalPos;
	}
	//構造体のX軸の代入
	void Set_S_DrawBase_AngX(const float *AngX) {
		M_S_DrawBase.AngX = *AngX;
	}
	//構造体のY軸の代入
	void Set_S_DrawBase_AngY(const float *AngY) {
		M_S_DrawBase.AngY = *AngY;
	}
	//構造体のZ軸の代入
	void Set_S_DrawBase_AngZ(const float *AngZ) {
		M_S_DrawBase.AngZ = *AngZ;
	}
protected:
	
private:
	/*変数*/
	S_DrawBase M_S_DrawBase;

	/*関数*/

	//表示構造体の初期化
	S_DrawBase Init_S_DrawBase(void);
};