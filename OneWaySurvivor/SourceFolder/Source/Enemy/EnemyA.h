#pragma once
#include"EnemyAi.h"
#include"../GameSource/Const.h"
#include"../GameSource/CharaBase.h"
#include"../GameSource/StructClass/Parts_Set_Data.h"

class C_EnemyA :public C_EnemyAi {
public:
	C_EnemyA(const D3DXMATRIX *GroundMat,const float *TransX);
	~C_EnemyA();
protected:
	//初期化ボディ
	void InitBody(void);

	//車のパーツを付ける処理
	void New_Set_EnemyCar_Parts(const int *Car_No);

	//銃のくっつけ
	void New_Car_Parts_Gun(const BODYDATA *CarData) {
		return;
	}
	void New_Car_Parts_Gun(std::vector<C_Parts_Set_Data*>M_Set_Data) {
		return;
	}

	//車のパーツをセットするための情報のセット
	void M_NewSet_CarPartsData(const int *CarParts_Type,const int CarParts_No,const int Draw_No);

private:
	//初期位置
	void InitPos(const D3DXMATRIX *GroundMat, const float * TransX);

	//パーツの情報の削除
	void Delete_All_Parts_Set_Data(void);

	//車のパーツの設定
	std::vector<C_Parts_Set_Data*>M_Parts_Set_Data;
};