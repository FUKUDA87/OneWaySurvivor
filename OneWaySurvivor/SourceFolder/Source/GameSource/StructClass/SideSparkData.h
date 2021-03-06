#pragma once
#include<vector>
#include"../Struct.h"

class C_SideSparkData
{
public:
	~C_SideSparkData();

	// 情報数
	unsigned int getDataNum(void) { return data.size(); }

	// 情報の追加
	void NewData(const s_CarType *judg, const s_CarType *hit, const D3DXMATRIX *initMat, const int *firstJudgType);
	
	// 情報渡し
	S_SideSparkData getData(const unsigned int *c) { return *data[*c]; }

	// 情報の削除
	void deleteData(unsigned int *c);
private:
	std::vector<S_SideSparkData*>data;

	// 検索
	bool JudgCarType(const s_CarType *t1, const s_CarType *t2);
};