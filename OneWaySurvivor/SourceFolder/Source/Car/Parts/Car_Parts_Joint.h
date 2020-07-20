#pragma once
#include"Car_Parts_Base.h"

class C_Car_Parts_Joint :public C_Car_Parts_Base {
public:
	C_Car_Parts_Joint(const S_CAR_PARTS_DATA *set_Data);
	~C_Car_Parts_Joint();

	//くっつきのデータ数渡し
	unsigned int Get_Juint_Data_Num(void) {
		return M_Joint_Data.size();
	}

	//くっつきのデータ渡し
	S_CAR_PARTS_DATA Get_Joint_Data(const unsigned int *DataNo) {
		return *M_Joint_Data[*DataNo];
	}


protected:

	std::vector<S_CAR_PARTS_DATA*>M_Joint_Data;

	//くっつきのデータ削除
	void Delete_ALL_Juint_Data(void);

	//くっつきのデータの作成
	void New_Joint_Data(const S_CAR_PARTS_DATA *Data);
private:

};