#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../../../GameSource/Struct.h"
#include"../../../GameSource/Const.h"
#include"../../../Const/Const_PartsTypeNo.h"

class C_MeshDataManagerBase {
public:
	//表示数の読み込み
	virtual int GetDrawNum(int CarNo,bool SaveFlg)=0;
	//表示設定の読み込み
	virtual S_CAR_PARTS_DATA GetDrawSet(int CarNo,const int *DrawNo, bool SaveFlg) = 0;
protected:
	//セーブ・ロード用
	FILE* fp;
	FILE *fp_b;
	char FName[100];

	//表示数-----------------------------------------
	//セーブ
	void SaveDN(int CarNo,int DrawNum);
	//ロード
	int LoadDN(int CarNo);
	//txtロードdatセーブ
	void LoadSaveDN(int CarNo);

	//表示情報----------------------------------------
	//セーブ
	void Save_Car_Parts_Data(int CarNo, const int *DrawNo,const S_CAR_PARTS_DATA *Par);
	//ロード
	S_CAR_PARTS_DATA Load_Car_Parts_Data(int CarNo, const int *DrawNo);
	//txtロードdatセーブ
	void LoadSave_Car_Parts_Data(int CarNo, const int *DrawNo);
	//初期化パーツ
	S_CAR_PARTS_DATA InitPartsDS(void);
	
private:

};