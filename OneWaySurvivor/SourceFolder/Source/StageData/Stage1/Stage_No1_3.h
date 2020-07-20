#pragma once
#include"Stage_No1_1.h"

class C_Stage_No1_3 :public C_Car_Pop_Update_1 {
public:
	C_Stage_No1_3();

	//出現している車のから情報の出現情報の作成
	void M_Car_Pop_Update(std::vector<C_EnemyAi*>enemy);

protected:
	//次の車
	C_Car_Pop_Base *Next_Pop(void);
private:

	//ボスの地面番号
	int M_BossWay_Number;

	//ボス以外のデータ削除
	void M_EnemyCar_Delete(void);
};