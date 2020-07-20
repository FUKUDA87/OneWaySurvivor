#pragma once
#include"Ground_Pop_Data.h"
#include<vector>
#include"../../GameSource/StructClass/Struct_Init.h"
#include"../../Const/Const_Ground_Type.h"

class C_Ground_Pop_Base {
public:
	C_Ground_Pop_Base();
	~C_Ground_Pop_Base();

	//情報渡し
	S_GROUND_INIT_DATA Get_Pop_Data(void);
	//出現後の処理
	void Ground_Pop_Rear(void);

protected:
	/*データのNew*/

	//初期化
	virtual void Init_Data(void) = 0;

	void New_Data(const S_GROUND_INIT_DATA* Data, const int GroundNum);
	void New_Data(const int *Grotype, const int GroundNum);

	

private:
	std::vector<C_Ground_Pop_Data*>M_C_Data;

	//全削除
	void Delete_All_Ground_Pop(void);

	const unsigned int M_Ground_PopNo;
};