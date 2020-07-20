#pragma once
#include"Car_Pop_Base.h"

class C_Car_Pop_Update_1 :public C_Car_Pop_Base {
public:
	//更新処理
	C_Car_Pop_Base *Update(const bool *Update_MoveFlg);
protected:
	//次のフェーズへ
	C_Car_Pop_Base *Next_Pop(void);

	//車のデータの初期化
	void New_All_Pop(void);
};