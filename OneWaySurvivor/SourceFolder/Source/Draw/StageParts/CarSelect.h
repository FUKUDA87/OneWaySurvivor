#pragma once
#include"../../GameSource/Judgment.h"
#include"../../GameSource/Struct.h"
#include<d3dx9.h>
#include"../Num/2D/Num2DA.h"

class C_CarSelect {
public:
	C_CarSelect(const D3DXVECTOR2* PosA, const D3DXVECTOR2* ScalA, const D3DXVECTOR2* ArrScal, const D3DXVECTOR2* ArrTransPos,const D3DXVECTOR2 *ScalNum);
	~C_CarSelect();
	//継承表示
	virtual void Draw2DAll(void);
	//画像のタッチ
	int Touch(void);
	//アップデート
	bool UpdateNo(const int *MeshNo);
	//No渡し
	int GetNo(void) {
		return No;
	}
protected:

	//初期化
	void InitCS(void);
	//表示
	void Draw2DCS(void);


	//画像構造体
	CHARA2D Back;
	BASE2D *Arr;
	TEXTURE ArrTex;

	Judg judg;

	//数の表示用クラス
	C_Num2DA *Num;
	//メッシュの番号
	int No;
private:
	//矢印数
	int ArrNum;
};