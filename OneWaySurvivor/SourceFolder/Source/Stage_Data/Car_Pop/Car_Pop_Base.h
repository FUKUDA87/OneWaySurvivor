#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"Car_Pop_Data.h"
#include<vector>
#include"../../GameSource/Const.h"
#include"../../Const/Const_Wave_Type.h"
#include"../../Const/Const_Rail_Type.h"
#include"../../Enemy/EnemyAi.h"

class C_Car_Pop_Base {
public:
	C_Car_Pop_Base();
	~C_Car_Pop_Base();

	//更新処理
	virtual C_Car_Pop_Base *Update(const bool *Update_MoveFlg)=0;

	//出現している車のから情報の出現情報の作成
	virtual void M_Car_Pop_Update(std::vector<C_EnemyAi*>enemy) {};

	//地面情報 
	virtual int Get_GroundNo(void) {
		return M_Ground_Type;
	}

	//車の出現の情報渡し
	S_CAR_INIT_DATA Get_Next_Car_Data(void);

	//車の出現可能渡し
	bool Get_Car_Pop_Flg(void);

	//車が出現した時にする処理
	void Car_Init_Rear(void);

	//ステージの構成情報渡し
	S_NOW_WAVE_DATA Get_Stage_Phase_Data(void) {
		return M_Stage_Data;
	}

	//今の敵数の取得
	void Set_Now_Enemy_Num(const int * Enemy_Num) {
		M_Stage_Data.Enemy_Alive_Num = *Enemy_Num;
	}
protected:
	//次のフェーズへ
	virtual C_Car_Pop_Base *Next_Pop(void) = 0;

	//車の情報の追加
	void New_Car_Data(const int CarType, const int CarNo, const int Count, const unsigned int GroundNo, const int WayNo);
	void New_Car_Data(const int CarType, const int CarNo, const int Count, const unsigned int GroundNo);

	//沸き時間のカウントダウン
	bool Update_Car_Count(void);

	//車のデータの初期化
	virtual void New_All_Pop(void)=0;

	//最後の車が出現後Flg
	bool M_Car_Pop_EndFlg;

	unsigned int Get_Pop_Data_Num(void) {
		return M_Car_Data.size();
	}

	//ステージのデータ
	S_NOW_WAVE_DATA M_Stage_Data;

	//車の出現可能
	bool M_Car_Pop_Flg;

	//生成される地面のタイプ
	int M_Ground_Type;

	//車のデータ
	std::vector<C_Car_Pop_Data*>M_Car_Data;

private:
	//全削除
	void Delete_All_Car(void);

	//車の番号
	const unsigned int Car_PopNo;

	//ステージの情報の初期化
	void Init_Stage_Data(void);
};