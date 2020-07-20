#pragma once
#include<vector>
#include"../Struct.h"

class C_SideSparkData
{
public:
	~C_SideSparkData();

	// î•ñ”
	unsigned int getDataNum(void) { return data.size(); }

	// î•ñ‚Ì’Ç‰Á
	void NewData(const s_CarType *judg, const s_CarType *hit, const D3DXMATRIX *initMat, const int *firstJudgType);
	
	// î•ñ“n‚µ
	S_SideSparkData getData(const unsigned int *c) { return *data[*c]; }

	// î•ñ‚Ìíœ
	void deleteData(unsigned int *c);
private:
	std::vector<S_SideSparkData*>data;

	// ŒŸõ
	bool JudgCarType(const s_CarType *t1, const s_CarType *t2);
};