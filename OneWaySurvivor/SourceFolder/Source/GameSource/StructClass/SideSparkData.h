#pragma once
#include<vector>
#include"../Struct.h"

class C_SideSparkData
{
public:
	~C_SideSparkData();

	// ���
	unsigned int getDataNum(void) { return data.size(); }

	// ���̒ǉ�
	void NewData(const s_CarType *judg, const s_CarType *hit, const D3DXMATRIX *initMat, const int *firstJudgType);
	
	// ���n��
	S_SideSparkData getData(const unsigned int *c) { return *data[*c]; }

	// ���̍폜
	void deleteData(unsigned int *c);
private:
	std::vector<S_SideSparkData*>data;

	// ����
	bool JudgCarType(const s_CarType *t1, const s_CarType *t2);
};