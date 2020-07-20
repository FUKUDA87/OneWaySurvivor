#pragma once
#include"Ground_Pop_Base.h"

class C_Ground_Pop_New {
public:
	C_Ground_Pop_New();
	C_Ground_Pop_New(const int GroundNo);
	C_Ground_Pop_New(C_Ground_Pop_Base* Pop);
	~C_Ground_Pop_New();

	//情報渡し
	S_GROUND_INIT_DATA Get_Pop_Data_N(void);
	//出現後の処理
	void Ground_Pop_Rear_N(void);

	//新規
	void New_Pop(C_Ground_Pop_Base* Pop);
	void New_Pop(const int *GroundNo);

	//地面番号の取得
	int Get_GroundNo(void) {
		return M_GroundNo;
	}

protected:

	//削除
	void Delete_C_Ground_Pop(void);

private:
	C_Ground_Pop_Base* M_C_Ground_Pop;

	//地面番号
	int M_GroundNo;

	//初期化
	void Init(void);
};